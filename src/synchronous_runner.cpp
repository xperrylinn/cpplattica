#include "synchronous_runner.h"
#include "simulation_result.h"
#include "simulation_state.h"
#include "game_of_life_controller.h"
#include "helpers.h"
#include "mpi_state_change.h"
#include <unordered_map>
#include <vector>
#include <unordered_set>


SynchronousRunner::SynchronousRunner() {}

SimulationResult SynchronousRunner::run(SimulationState& initial_state, BasicController& controller, int num_steps) {
    // std::cout << "SynchronousRunner::run(SimulationState initial_state, BasicController controller, int num_steps)" << std::endl;
    SimulationResult result = controller.instantiate_result(initial_state);
    controller.pre_run(initial_state);
    SimulationState live_state = initial_state;
    this->_run(initial_state, result, live_state, controller, num_steps);
    result.set_output(live_state);
    return result;
}

SimulationResult SynchronousRunner::_run(
    SimulationState& initial_state,
    SimulationResult& result,
    SimulationState& live_state,
    BasicController& controller,
    int num_steps
) {
    // Allocate a buffer to receive all the data
    MPI_Datatype mpi_state_change_type = create_mpi_state_change_type();

    // std::cout << "SynchronousRunner::_run(SimulationState initial_state, SimulationResult result, SimulationState live_state, BasicController controller, int num_steps)" << std::endl;
    for (int i = 0 ; i < num_steps; i += 1) {
        std::vector<mpi_state_change> state_updates = this->_take_step(live_state, controller);
        // TODO: MPI COMMUNICATION HERE
        // Broadcast number of changes to all processes

        // Explicit barrier to make sure all processes have completed their updates
        MPI_Barrier(MPI_COMM_WORLD);

        // Each process sends its size
        int num_changes = state_updates.size();
        std::vector<int> all_sizes(this->num_procs);
        MPI_Allgather(&num_changes, 1, MPI_INT, all_sizes.data(), 1, MPI_INT, MPI_COMM_WORLD);

        // Calculate the total number of changes and the displacements for each rank
        int total_changes = 0;
        std::vector<int> displs(this->num_procs);
        for (int i = 0; i < this->num_procs; ++i) {
            displs[i] = total_changes;
            total_changes += all_sizes[i];
        }

        std::vector<mpi_state_change> recv_buffer(total_changes);

        // Use MPI_Allgatherv to gather the data from all ranks
        MPI_Allgatherv(
            state_updates.data(), 
            num_changes, 
            mpi_state_change_type, 
            recv_buffer.data(), 
            all_sizes.data(), 
            displs.data(), 
            mpi_state_change_type, 
            MPI_COMM_WORLD
        );

        // Print the received data on each rank
        // for (int j = 0; j < total_changes; j += 1) {
        //     std::cout << "step: " << i;
        //     std::cout << ", rank: " << rank;
        //     std::cout << " recv data: site_id: " << recv_buffer[j].site_id;
        //     std::cout << ", new_state: " << recv_buffer[j].new_state;
        //     std::cout << ", old_state: " << live_state.get_site_state(recv_buffer[j].site_id) << std::endl;
        // }

        // Update ranks live state
        for (const auto& state_change: recv_buffer) {
            live_state.set_site_state(state_change.site_id, state_change.new_state);
        }

        // Print the size of state_updates
        // std::cout << "step: " << i << ", rank: " << rank << ", state_updates.size(): " << state_updates.size() << std::endl;
        
        result.add_step(state_updates);
    }

    // Explicit barrier to make sure all processes have completed their updates
    MPI_Barrier(MPI_COMM_WORLD);

    // Gather all results into rank 0
    // Flatten the local 2D vector into a 1D vector
    std::vector<mpi_state_change> flat_local_changes;
    for (const auto& step_diffs : result.get_diffs()) {
        flat_local_changes.insert(flat_local_changes.end(), step_diffs.begin(), step_diffs.end());
    }

    // Get the size of the flattened local vector
    int local_size = flat_local_changes.size();

    // Gather the sizes from all ranks to rank 0
    std::vector<int> all_sizes(this->num_procs);
    MPI_Gather(&local_size, 1, MPI_INT, all_sizes.data(), 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Rank 0 computes the displacement and total size
    std::vector<int> displs(this->num_procs, 0);
    int total_size = 0;
    if (this->rank == 0) {
        for (int i = 0; i < this->num_procs; ++i) {
            displs[i] = total_size;
            total_size += all_sizes[i];
        }
    }

    // Rank 0 allocates the receive buffer
    std::vector<mpi_state_change> all_changes(total_size);

    // Gather all the flattened vectors to rank 0
    MPI_Gatherv(flat_local_changes.data(), local_size, mpi_state_change_type,
                all_changes.data(), all_sizes.data(), displs.data(), mpi_state_change_type, 0, MPI_COMM_WORLD);

    // Reconstruct the nested structure on rank 0
    if (this->rank == 0) {
        std::vector<std::vector<mpi_state_change>> gathered_changes(this->num_procs);
        int offset = 0;
        for (int i = 1; i < this->num_procs; i += 1) {  // All ranks but zero
            std::vector<mpi_state_change> inner_vec(
                all_changes.begin() + offset,
                all_changes.begin() + offset + all_sizes[i]
            );
            gathered_changes[i] = inner_vec;
            offset += all_sizes[i];
        }

        // Print the gathered data for verification
        for (int i = 0; i < gathered_changes.size(); ++i) {
            for (const auto& change : gathered_changes[i]) {
                std::cout << "{\"step\": " << i << ", \"src_rank\": " << change.src_rank <<  ", \"site_id\": " << change.site_id << ", \"new_state\": " << change.new_state << "}," << std::endl;
            }
        }

        result.set_diffs(gathered_changes);
    }

    return result;
}

std::vector<mpi_state_change> SynchronousRunner::_take_step(
    SimulationState& state,
    BasicController& controller
) {
    // std::cout << "_take_step(SimulationState state, BasicController controller)" << std::endl;
    std::vector<int> site_ids = state.get_rank_site_ids();
    std::cout << "rank: " << this->rank << ", site_ids: ";
    print_vector(site_ids);
    std::vector<mpi_state_change> updated_sites(this->_step_batch(site_ids, state, controller));
    return updated_sites;
}

std::vector<mpi_state_change> SynchronousRunner::_step_batch(
    std::vector<int>& id_batch,
    SimulationState& previous_state,
    BasicController& controller
) {
    // std::cout << "SynchronousRunner::_step_batch(std::vector<int> id_batch, SimulationState previous_state, BasicController controller)" << std::endl;
    std::vector<mpi_state_change> updated_states;
    updated_states.reserve(id_batch.size());
    for (const auto& site_id : id_batch) {
        const int current_state = previous_state.get_site_state(site_id);
        int updated_state = controller.get_state_update(site_id, previous_state);
        if (current_state != updated_state) {
            updated_states.push_back({this->rank, site_id, updated_state});
        } 
    }
    return updated_states;
}
