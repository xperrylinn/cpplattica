#include "simulation_result.h"
#include "mpi_state_change.h"


SimulationResult::SimulationResult() {}

SimulationResult::SimulationResult(SimulationState initial_state) {
    // std::cout << "SimulationResult(SimulationState initial_state)" << std::endl;
    this->initial_state = initial_state;
    this->_diffs = {};
}

void SimulationResult::add_step(std::vector<mpi_state_change> state_change) {
    // std::cout << "SimulationResult::add_step(std::unordered_map<int, int> state)" << std::endl;
    this->_diffs.push_back(state_change);
}

void SimulationResult::set_output(SimulationState step) {
    // std::cout << "SimulationResult::set_output(SimulationState step)" << std::endl;
    this->output = step;
}
