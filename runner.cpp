#include "runner.h"
#include "basic_controller.h"
#include "simulation_result.h"
#include "simulation_state.h"


Runner::Runner() {}


SimulationResult Runner::run(SimulationState& initial_state, BasicController& controller, int num_steps) {
    std::cout << "Runner::run(SimulationState initial_state, BasicController controller, int num_steps)" << std::endl;
    return SimulationResult();
}

SimulationResult Runner::_run(
    SimulationState& initial_state,
    SimulationResult& result,
    SimulationState& live_state,
    BasicController& controller,
    int num_steps
) {
    std::cout << "Runner::run(SimulationState initial_state, BasicController controller, int num_steps)" << std::endl;
    return SimulationResult();
}

SimulationResult Runner::_take_step(
    SimulationState& state,
    BasicController& controller
) {
    std::vector<int> site_ids = state.get_site_ids();
    return SimulationResult();
}

std::vector<int> Runner::_step_batch(
    std::vector<int>& id_batch,
    SimulationState& previous_state,
    BasicController& controller
) {
    return {};
}
