#include "game_of_life_controller.h"
#include "moore_neighborhood_builder.h"


void GameOfLifeController::pre_run(SimulationState initial_state) {
    std::cout << "GameOfLifeController::pre_run(SimulationState initial_state)" << std::endl;
    this->neighborhood = MooreNeighborhoodBuilder(1, 2).get(this->structure);
}

int GameOfLifeController::get_state_update(int site_id, SimulationState prev_state) {
    std::cout << "GameOfLifeController::get_state_update(int site_id, SimulationState prev_state)" << std::endl;
    int alive_neighbor_count = 0;
    int dead_neighbor_count = 0;

    return 0;
}

GameOfLifeController::GameOfLifeController(PeriodicStructure structure) {
    std::cout << "GameOfLifeController::GameOfLifeController(PeriodicStructure structure)" << std::endl;
    this->structure = structure;
}