#ifndef GAMEOFLIFECONTROLLER_H
#define GAMEOFLIFECONTROLLER_H
#include "basic_controller.h"
#include "simulation_state.h"
#include "periodic_structure.h"
#include "neighborhood.h"


class GameOfLifeController : public BasicController {
    public:
        void pre_run(SimulationState initial_state) override;
        GameOfLifeController(PeriodicStructure structure);
        const int get_state_update(int site_id, SimulationState curr_state) const override;
};

#endif
