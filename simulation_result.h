#ifndef SIMULATIONRESULT_H
#define SIMULATIONRESULT_H
#include "simulation_state.h"


class SimulationResult {
    public:
        SimulationState initial_state;

        SimulationResult();
        SimulationResult(SimulationState initial_state);
};

#endif