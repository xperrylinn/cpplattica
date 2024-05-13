#include <chrono>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <mpi.h>
#include <random>
#include <vector>
#include <armadillo>
#include "phases_set.h"
#include "lattice.h"
#include "square_grid_lattice_2d.h"
#include "discrete_grid_setup.h"
#include "game_of_life_controller.h"
#include "synchronous_runner.h"
#include "simulation.h"
#include "helpers.h"


int main(int argc, char** argv) {

    // Test DiscreteGridSetup
    std::vector<std::string> phases = {"alive", "dead"};    
    PhaseSet phase_set = PhaseSet(phases);
    std::cout << "created PhaseSet" << std::endl;
    int size = 4;
    DiscreteGridSetup setup = DiscreteGridSetup(phase_set);
    std::cout << "created DiscreteGridSetup" << std::endl;
    Simulation starting_state = setup.setup_noise(phase_set, size);
    std::cout << "created Simulation" << std::endl;
    GameOfLifeController controller(starting_state.structure);
    std::cout << "created GameOfLifeController" << std::endl;
    SynchronousRunner runner;
    std::cout << "created SynchronousRunner" << std::endl;
    runner.run(starting_state.state, controller, 10);

}