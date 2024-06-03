#include "simulation_result.h"


SimulationResult::SimulationResult() {}

SimulationResult::SimulationResult(SimulationState initial_state) {
    // std::cout << "SimulationResult(SimulationState initial_state)" << std::endl;
    this->initial_state = initial_state;
    this->states = {};
}

void SimulationResult::add_step(std::unordered_map<int, int> state) {
    // std::cout << "SimulationResult::add_step(std::unordered_map<int, int> state)" << std::endl;
    this->states.push_back(state);
}

void SimulationResult::set_output(SimulationState step) {
    // std::cout << "SimulationResult::set_output(SimulationState step)" << std::endl;
    this->output = step;
}
