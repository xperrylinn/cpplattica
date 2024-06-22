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
    // Get the MPI version and subversion
    int version, subversion;
    MPI_Get_version(&version, &subversion);
    std::cout << "mpi_version: " << version << "." << subversion << std::endl;

    // Check if the correct number of arguments are provided
    if (argc != 3) {
        if (rank == 0) {  // Only print error message from rank 0 to avoid clutter
            std::cerr << "Usage: " << argv[0] << " <size> <steps>" << std::endl;
        }
        MPI_Finalize();
        return 1;
    }
    // Get the command line arguments
    int size = std::stoi(argv[1]);
    int steps = std::stoi(argv[2]);

    // Start timer
    TimePoint startTime = start_timer();
    // Test DiscreteGridSetup
    std::vector<std::string> phases = {"alive", "dead"};    
    PhaseSet phase_set = PhaseSet(phases);
    // std::cout << "created PhaseSet" << std::endl;

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

    std::ostringstream oss;
    oss << "rank: " << rank << ", size: " << size << ", steps: " << steps << ", time: " << elapsed_time << std::endl; 
    std::string elapsed_time_data = oss.str();
    // std::cout << "completed SynchronousRunner run function call" << std::endl;

    if (rank == 0) {
        oss.str("");
        oss.clear();
        oss << "./sim_structure_rank_" << rank << "_size_" << size << "_nsteps_" << steps << ".json";
        std::string sim_structure_file_path = oss.str();
        oss.str("");
        oss.clear();
        oss << "./sim_result_rank_" << rank << "_size_" << size << "_nsteps_" << steps << ".json";
        std::string sim_result_file_path = oss.str();
        oss.str("");
        oss.clear();
        oss << "./elapsed_time_rank_" << rank << "_size_" << size << "_nsteps_" << steps << ".txt";
        std::string elapsed_time_file_path = oss.str();

        std::string sim_structure_json = gol_simulation.structure.to_json();
        write_string_to_file(sim_structure_file_path, sim_structure_json);

        std::string sim_result_json = result.to_json();
        write_string_to_file(sim_result_file_path, sim_result_json);

        write_string_to_file(elapsed_time_file_path, elapsed_time_data);
    }
    // std::cout << "completed writing to files" << std::endl;

    // for (const auto& site : gol_simulation.structure.sites()) {
    //     std::cout << "site.id: " << site.get_site_id() << ", site.rank: " << site.get_site_rank() << std::endl;
    //     std::cout << "site.location:" << std::endl;
    //     std::cout << site.get_location() << std::endl;
    // }
    
    // std::vector<std::vector<mpi_state_change>> sim_result_diffs = result.get_diffs();
    // for (int i = 0; i < sim_result_diffs.size() && rank == 0; i  += 1) {
    //     for (const auto& state_change : sim_result_diffs[i]) {
    //         std::cout << "step: " << i;
    //         std::cout << ", src_rank: " << state_change.src_rank;
    //         std::cout << ", site_id: " << state_change.site_id;
    //         std::cout << ", new_state: " << state_change.new_state;
    //         std::cout << ", total_diff_per_step: " << sim_result_diffs[i].size();
    //         std::cout << std::endl;
    //     }
    // }

    // Close MPI
    MPI_Finalize(); 
}