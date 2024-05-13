#include "game_of_life_controller.h"
#include "moore_neighborhood_builder.h"


void GameOfLifeController::pre_run(SimulationState initial_state) {
    this->neighborhood = MooreNeighborhoodBuilder().get(this->structure);
}

int GameOfLifeController::get_state_update(int site_id, SimulationState prev_state) {
    int alive_neighbor_count = 0;
    int dead_neighbor_count = 0;

    return 0;
}

GameOfLifeController::GameOfLifeController(PeriodicStructure structure) {
    this->structure = structure;
}