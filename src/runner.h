#ifndef RUNNER_H
#define RUNNER_H
#include "basic_controller.h"
#include "simulation_result.h"
#include "simulation_state.h"


class Runner {
    public:
        Runner();

        SimulationResult run(SimulationState& initial_state, BasicController& controller, int num_steps);
    private:
        virtual SimulationResult _run(
            SimulationState& initial_state,
            SimulationResult& result,
            SimulationState& live_state,
            BasicController& controller,
            int num_steps
        );
        virtual std::unordered_map<int, int> _take_step(
            SimulationState& state,
            BasicController& controller
        );
        virtual std::unordered_map<int, int> _step_batch(
            std::vector<int>& id_batch,
            SimulationState& previous_state,
            BasicController& controller
        );
};

#endif