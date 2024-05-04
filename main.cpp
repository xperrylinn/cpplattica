#include "phases_set.h"
#include "lattice.h"
#include "square_grid_lattice_2d.h"
#include "discrete_grid_setup.h"
#include "simulation.h"
#include "helpers.h"
#include <chrono>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <mpi.h>
#include <random>
#include <vector>
#include <armadillo>


int main(int argc, char** argv) {

    // Test DiscreteGridSetup
    std::vector<std::string> phases = {"alive", "dead"};    
    PhaseSet phase_set = PhaseSet(phases);
    std::cout << "creating PhaseSet" << std::endl;
    int size = 4;
    DiscreteGridSetup setup = DiscreteGridSetup(phase_set);
    std::cout << "creating DiscreteGridSetup" << std::endl;
    Simulation starting_state = setup.setup_noise(phase_set, size);
    std::cout << "created Simulation" << std::endl;
}