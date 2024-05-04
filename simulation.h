#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <cassert>
#include <cmath>
#include <armadillo>
#include "simulation_state.h"
#include "periodic_structure.h"


class Simulation {
    public:
        SimulationState state;
        PeriodicStructure structure;

        Simulation();
        Simulation(SimulationState state, PeriodicStructure structure);
};

#endif
