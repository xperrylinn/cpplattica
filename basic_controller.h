#ifndef BASIC_CONTROLLER_H
#define BASIC_CONTROLLER_H

#include <vector>
#include <string>
#include <unordered_map>
#include "simulation_state.h"
#include "simulation_result.h"


class BasicController {
    public:
        int get_state_update(int site_id, SimulationState prev_state);
        virtual void pre_run(SimulationState initial_state);
        int get_random_site(SimulationState state);
        SimulationResult instantiate_result(SimulationState starting_state);
};

#endif
