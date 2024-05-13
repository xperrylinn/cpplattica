#include "simulation_result.h"


SimulationResult::SimulationResult() {}

SimulationResult::SimulationResult(SimulationState initial_state) {
    std::cout << "SimulationResult(SimulationState initial_state)" << std::endl;
    this->initial_state = initial_state;
}
