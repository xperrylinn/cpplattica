#ifndef SYNCHRONOUSRUNNER_H
#define SYNCHRONOUSRUNNER_H
#include "runner.h"
#include "simulation_state.h"
#include "basic_controller.h"
#include "simulation_result.h"


class SynchronousRunner : public Runner {
    public:
        SynchronousRunner();

        SimulationResult _run(SimulationState initial_state, BasicController controller, int num_steps);
};

#endif
