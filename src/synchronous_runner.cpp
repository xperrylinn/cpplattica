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
    // std::cout << "SynchronousRunner::_run(SimulationState initial_state, SimulationResult result, SimulationState live_state, BasicController controller, int num_steps)" << std::endl;
    for (int i = 0 ; i < num_steps; i += 1) {
        std::unordered_map<int, int> state_updates = this->_take_step(live_state, controller);
        // TODO: MPI COMMUNICATION HERE

        // Create data structure for broadcasting state updates from this rank
        std::vector<int> updated_site_ids = unordered_map_keys_to_vec(state_updates);
        std::vector<mpi_state_change> send_buffer;
        for (const auto& site_id : updated_site_ids) {
            std::vector<int> neighboring_site_ids = controller.neighborhood.get_graph().at(site_id);
            std::unordered_set<int> neighboring_site_ids_set(neighboring_site_ids.begin(), neighboring_site_ids.end());
            mpi_state_change state_change = {site_id, state_updates[site_id]};
            send_buffer.push_back(state_change);
        }

        // Broadcast number of changes to all processes

        // Each process sends its size
        int num_changes = send_buffer.size();
        std::vector<int> all_sizes(this->num_procs);
        std::cout << "FAILURE 2" << this->num_procs << std::endl;
        MPI_Allgather(&num_changes, 1, MPI_INT, all_sizes.data(), 1, MPI_INT, MPI_COMM_WORLD);

        // Calculate the total number of changes and the displacements for each rank
        int total_changes = 0;
        std::vector<int> displs(this->num_procs);
        for (int i = 0; i < this->num_procs; ++i) {
            displs[i] = total_changes;
            total_changes += all_sizes[i];
        }

        // Allocate a buffer to receive all the data
        std::cout << "FAILURE 2" << std::endl;
        MPI_Datatype mpi_state_change_type = create_mpi_state_change_type();

        std::vector<mpi_state_change> recv_buffer(total_changes);

        // Use MPI_Allgatherv to gather the data from all ranks
        MPI_Allgatherv(
            send_buffer.data(), 
            num_changes, 
            mpi_state_change_type, 
            recv_buffer.data(), 
            all_sizes.data(), 
            displs.data(), 
            mpi_state_change_type, 
            MPI_COMM_WORLD
        );

        // Print the received data on each rank
        std::cout << "rank " << rank << " received data:" << std::endl;
        for (int i = 0; i < total_changes; ++i) {
            std::cout << "  site_id=" << recv_buffer[i].site_id 
                    << ", new_state=" << recv_buffer[i].new_state << std::endl;
        }

        

        // Synchronization

        result.add_step(state_updates);
    }
    return result;
}

std::unordered_map<int, int> SynchronousRunner::_take_step(
    SimulationState& state,
    BasicController& controller
) {
    // std::cout << "_take_step(SimulationState state, BasicController controller)" << std::endl;
    std::vector<int> site_ids = state.get_site_ids();
    std::unordered_map<int, int> updated_sites(this->_step_batch(site_ids, state, controller));
    return updated_sites;
}

std::unordered_map<int, int> SynchronousRunner::_step_batch(
    std::vector<int>& id_batch,
    SimulationState& previous_state,
    BasicController& controller
) {
    // std::cout << "SynchronousRunner::_step_batch(std::vector<int> id_batch, SimulationState previous_state, BasicController controller)" << std::endl;
    std::unordered_map<int, int> updated_states;
    updated_states.reserve(id_batch.size());
    for (const auto& site_id : id_batch) {
        const int current_state = previous_state.get_site_state(site_id);
        int updated_state = controller.get_state_update(site_id, previous_state);
        if (current_state != updated_state) {
            updated_states[site_id] = updated_state;
        } 
    }
    return updated_states;
}
