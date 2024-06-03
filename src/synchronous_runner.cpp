#include "synchronous_runner.h"
#include "simulation_result.h"
#include "simulation_state.h"
#include "game_of_life_controller.h"


SynchronousRunner::SynchronousRunner() {}

SimulationResult SynchronousRunner::_run(
    SimulationState& initial_state,
    SimulationResult& result,
    SimulationState& live_state,
    BasicController& controller,
    int num_steps
) {
    // std::cout << "SynchronousRunner::_run(SimulationState initial_state, SimulationResult result, SimulationState live_state, BasicController controller, int num_steps)" << std::endl;
    for (int i = 0 ; i < num_steps; i += 1) {
        // std::cout << "Step " << i << std::endl;
        std::unordered_map<int, int> state_updates = this->_take_step(live_state, controller);
        result.add_step(state_updates);
    }
    return result;
}

SimulationResult SynchronousRunner::run(SimulationState& initial_state, BasicController& controller, int num_steps) {
    // std::cout << "SynchronousRunner::run(SimulationState initial_state, BasicController controller, int num_steps)" << std::endl;
    SimulationResult result = controller.instantiate_result(initial_state);
    controller.pre_run(initial_state);
    SimulationState live_state = initial_state;
    this->_run(initial_state, result, live_state, controller, num_steps);
    result.set_output(live_state);
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
    for (const auto& site_id : id_batch) {
        int updated_state = controller.get_state_update(site_id, previous_state);
        updated_states[site_id] = updated_state;
    }
    return updated_states;
}
