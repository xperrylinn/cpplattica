#include "game_of_life_controller.h"
#include "moore_neighborhood_builder.h"
#include "helpers.h"


GameOfLifeController::GameOfLifeController(PeriodicStructure structure) : BasicController(structure) {
    // std::cout << "GameOfLifeController::GameOfLifeController(PeriodicStructure structure)" << std::endl;
}

void GameOfLifeController::pre_run(SimulationState initial_state) {
    // std::cout << "GameOfLifeController::pre_run(SimulationState initial_state)" << std::endl;
    this->neighborhood = MooreNeighborhoodBuilder(1, 2).get(this->structure);
}

const int GameOfLifeController::get_state_update(int site_id, SimulationState curr_state) const {
    // std::cout << "GameOfLifeController::get_state_update(int site_id, SimulationState previous_state)" << std::endl;
    int alive_neighbor_count = 0;
    int dead_neighbor_count = 0;

    std::vector<int> neighbor_ids = this->neighborhood.get_graph().at(site_id);

    for (const auto& neighbor_id : neighbor_ids) {
        int neighbor_state = curr_state.get_site_state(neighbor_id);
        if (neighbor_state == 1) {
            alive_neighbor_count += 1;
        } else {
            dead_neighbor_count  += 1;
        }
    }

    int current_site_state = curr_state.get_site_state(site_id);

    int new_state;
    if (current_site_state == 1 && (alive_neighbor_count == 2 || alive_neighbor_count == 3)) {
        new_state = 1;
    } else if (current_site_state == 0 && alive_neighbor_count == 3) {
        new_state = 1;
    } else {
        new_state = 0;
    }
    
    return new_state;
}
