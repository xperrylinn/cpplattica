#include "simulation.h"


Simulation::Simulation() {}

Simulation::Simulation(SimulationState state, PeriodicStructure structure) {
    // std::cout << "Simulation(SimulationState state, PeriodicStructure structure)" << std::endl;
    this->state = state;
    this->structure = structure;
}