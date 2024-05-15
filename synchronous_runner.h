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

        SimulationResult run(SimulationState initial_state, GameOfLifeController controller, int num_steps);
};

#endif
