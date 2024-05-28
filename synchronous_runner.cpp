#include "synchronous_runner.h"
#include "simulation_result.h"
#include "simulation_state.h"
#include "game_of_life_controller.h"


SynchronousRunner::SynchronousRunner() {}

SimulationResult SynchronousRunner::_run(
    SimulationState initial_state,
    SimulationResult result,
    SimulationState live_state,
    BasicController controller,
    int num_steps
) {
    std::cout << "SynchronousRunner::_run(SimulationState initial_state, SimulationResult result, SimulationState live_state, BasicController controller, int num_steps)" << std::endl;
    return SimulationResult();
}

SimulationResult SynchronousRunner::run(SimulationState initial_state, GameOfLifeController controller, int num_steps) {
    std::cout << "SynchronousRunner::run(SimulationState initial_state, BasicController controller, int num_steps)" << std::endl;
    SimulationResult result = controller.instantiate_result(initial_state);
    controller.pre_run(initial_state);
    // TODO: live_state = initial_state.copy()
    SimulationState live_state = initial_state;
    // self._run(initial_state, result, live_state, controller, num_steps, verbose)
    this->_run(initial_state, result, live_state, controller, num_steps);
    // TODO: result.set_output(live_state)
    return result;
}
