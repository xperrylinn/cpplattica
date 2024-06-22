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
        std::cout << "step: " << i << ", rank: " << rank << ", state_updates.size(): " << state_updates.size() << ", recv_buffer.size(): " << recv_buffer.size() << std::endl;
        
        result.add_step(recv_buffer);
    }
    result.set_output(live_state);
    return result;
}

std::vector<mpi_state_change> SynchronousRunner::_take_step(
    SimulationState& state,
    BasicController& controller
) {
    // std::cout << "_take_step(SimulationState state, BasicController controller)" << std::endl;
    std::vector<int> site_ids = state.get_rank_site_ids();

    // Print neighbors for debugging
    // std::cout << "rank: " << this->rank << ", site_ids: ";
    // print_vector(site_ids);

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
