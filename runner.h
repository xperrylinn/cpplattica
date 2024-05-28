#ifndef RUNNER_H
#define RUNNER_H
#include "basic_controller.h"
#include "simulation_result.h"
#include "simulation_state.h"


class Runner {
    public:
        Runner();

        SimulationResult run(SimulationState initial_state, BasicController controller, int num_steps);
    private:
        virtual SimulationResult _run(
            SimulationState initial_state,
            SimulationResult result,
            SimulationState live_state,
            BasicController controller,
            int num_steps
        );
};

#endif
