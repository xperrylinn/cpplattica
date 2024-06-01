#ifndef SYNCHRONOUSRUNNER_H
#define SYNCHRONOUSRUNNER_H
#include "runner.h"
#include "simulation_state.h"
#include "basic_controller.h"
#include "game_of_life_controller.h"
#include "simulation_result.h"


class SynchronousRunner : public Runner {
    public:
        SynchronousRunner();

        SimulationResult run(SimulationState& initial_state, BasicController& controller, int num_steps);
    private:
        virtual SimulationResult _run(
            SimulationState& initial_state,
            SimulationResult& result,
            SimulationState& live_state,
            BasicController& controller,
            int num_steps
        ) override;
        SimulationResult _take_step(
            SimulationState& state,
            BasicController& controller
        ) override;
        std::vector<int> _step_batch(
            std::vector<int>& id_batch,
            SimulationState& previous_state,
            BasicController& controller
        ) override;
};

#endif
