#ifndef SIMULATIONRESULT_H
#define SIMULATIONRESULT_H
#include <unordered_map>
#include "simulation_state.h"


class SimulationResult {
    public:
        SimulationState initial_state;
        SimulationState first_step;
        SimulationState last_step;
        SimulationState output;
        std::vector<std::unordered_map<int, int>> states;

        SimulationResult();
        SimulationResult(SimulationState initial_state);
        void add_step(std::unordered_map<int, int> state);
        void set_output(SimulationState step);
};

#endif