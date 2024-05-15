#ifndef GAMEOFLIFECONTROLLER_H
#define GAMEOFLIFECONTROLLER_H
#include "basic_controller.h"
#include "simulation_state.h"
#include "periodic_structure.h"
#include "neighborhood.h"


class GameOfLifeController : public BasicController {
    public:
        PeriodicStructure structure;
        Neighborhood neighborhood;

        int get_state_update(int site_id, SimulationState prev_state);
        void pre_run(SimulationState initial_state);
        GameOfLifeController(PeriodicStructure structure);
};

#endif
