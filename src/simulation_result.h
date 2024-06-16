#ifndef SIMULATIONRESULT_H
#define SIMULATIONRESULT_H
#include <unordered_map>
#include "simulation_state.h"
#include "mpi_state_change.h"


class SimulationResult {
    public:
        SimulationState initial_state;
        SimulationState first_step;
        SimulationState last_step;
        SimulationState output;

        SimulationResult();
        SimulationResult(SimulationState initial_state);
        void add_step(std::vector<mpi_state_change> state_changes);
        void set_output(SimulationState step);
    private:
        std::vector<std::vector<mpi_state_change>> _diffs;      
};

#endif