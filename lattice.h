#ifndef LATTICE_H
#define LATTICE_H

// #include <Eigen/Dense>
#include <vector>
#include <cassert>
#include <cmath>
#include <armadillo>


class Lattice {
    public:
        std::vector<std::vector<double>> vecs;
        std::vector<bool> periodic;
        int dim;
        arma::mat mat;
        std::vector<double> vec_lengths;

        Lattice();
        Lattice(const std::vector<std::vector<double>>& vecs, bool periodic = true);

    private:
        
        std::vector<bool> _periodic_bool;   // Not used anywhere
        arma::mat _matrix;
        arma::mat _inv_matrix;
};

#endif // LATTICE_H
