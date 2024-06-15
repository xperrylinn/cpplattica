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

    // Init MPI
    int num_procs, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::cout << "num_procs: " << num_procs << ", rank: " << rank <<std::endl;

    // Start timer
    TimePoint startTime = start_timer();
    // Test DiscreteGridSetup
    std::vector<std::string> phases = {"alive", "dead"};    
    PhaseSet phase_set = PhaseSet(phases);
    // std::cout << "created PhaseSet" << std::endl;
    int size = 2;
    int steps = 10;
    DiscreteGridSetup setup = DiscreteGridSetup(phase_set);
    // std::cout << "created DiscreteGridSetup" << std::endl;
    Simulation gol_simulation = setup.setup_noise(phase_set, size, num_procs, rank);
    // std::cout << "created Simulation" << std::endl;
    GameOfLifeController controller(gol_simulation.structure);
    // std::cout << "created GameOfLifeController" << std::endl;
    SynchronousRunner runner;
    runner.rank = rank;
    runner.num_procs = num_procs;
    // std::cout << "created SynchronousRunner" << std::endl;
    SimulationResult result = runner.run(gol_simulation.state, controller, steps);
    // Stop timer
    double elapsed_time = stop_timer(startTime);
    std::cout << "rank: " << rank << ", size: " << size << ", steps: " << steps << ", time: " << elapsed_time << std::endl; 
    // std::cout << "completed SynchronousRunner run function call" << std::endl;
    std::string file_path = "./output_rank_" + std::to_string(rank) + ".json";
    std::string json = gol_simulation.structure.to_json();
    write_string_to_file(file_path, json);
    // std::cout << "completed writing JSON to file" << std::endl;

    // for (const auto& site : gol_simulation.structure.sites()) {
    //     std::cout << "site.id: " << site.get_site_id() << ", site.rank: " << site.get_site_rank() << std::endl;
    //     std::cout << "site.location:" << std::endl;
    //     std::cout << site.get_location() << std::endl;
    // }

    // Close MPI
    MPI_Finalize(); 
}