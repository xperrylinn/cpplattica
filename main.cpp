#include "phases_set.h"
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

}