#include "phases_set.h"
#include "lattice.h"
#include "square_grid_lattice_2d.h"
#include <chrono>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <mpi.h>
#include <random>
#include <vector>
#include <armadillo>


// ==============
// Main Function
// ==============

int main(int argc, char** argv) {

    // Test classes and stuff
    std::vector<std::string> phases = {"alive", "dead"};    
    PhaseSet phase_set = PhaseSet(phases);

    for (int i = 0; i < 2; i += 1) {
        std::cout << i << " -> " << phase_set.get_phase(i) << std::endl;
    }

    // Test armadillio is working
    arma::mat A(4, 5, arma::fill::randu);
    arma::mat B(4, 5, arma::fill::randu);
  
    std::cout << A*B.t() << std::endl;

    // Test Lattice
    std::vector<std::vector<double>> vecs = {
        {0.0, 1.0},
        {1.0, 0.0}
    };
    Lattice lattice(vecs);

    // Test SquareGridLattice2D
    SquareGridLattice2D square_grid_lattice_2d;
    for (const auto& vec : square_grid_lattice_2d.lattice_vecs) {
        for (const auto& element : vec) {
            std::cout << element << ", ";
        }
        std::cout << std::endl;
    }


}