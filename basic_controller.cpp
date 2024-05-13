#include <cstdlib>
#include "basic_controller.h"
#include "simulation_state.h"
#include "simulation_result.h"
#include "simulation_state.h"


int BasicController::get_random_site(SimulationState state) {
    std::cout << "BasicController::get_random_site(SimulationState state)" << std::endl;
    return rand() % state.num_sites();
}

SimulationResult BasicController::instantiate_result(SimulationState starting_state) {
    std::cout << "BasicController::instantiate_result(SimulationState starting_state)" << std::endl;
    SimulationResult result(starting_state);
    return result;
}
