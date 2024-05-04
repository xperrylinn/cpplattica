#ifndef LATTICE_H
#define LATTICE_H

// #include <Eigen/Dense>
#include <vector>
#include <cassert>
#include <cmath>
#include <armadillo>


arma::vec periodize(const arma::vec& frac_coords, const arma::vec& periodic);

class Lattice {
    public:
        std::vector<std::vector<double>> vecs;
        arma::vec periodic;
        int dim;
        arma::mat mat;
        std::vector<double> vec_lengths;

        Lattice();
        Lattice(const std::vector<std::vector<double>>& vecs, bool periodic = true);
        Lattice(const std::vector<std::vector<double>>& vecs, arma::vec periodic);

        arma::vec get_cartesian_coords(const arma::vec& fractional_coords);
        Lattice get_scaled_lattice(const std::vector<int>& num_cells);
        arma::vec get_periodized_cartesian_coords(const arma::vec& cart_coords);
        arma::vec get_fractional_coords(const arma::vec& cart_coords);
    private:
        
        std::vector<bool> _periodic_bool;   // Not used anywhere
        arma::mat _matrix;
        arma::mat _inv_matrix;
};

#endif // LATTICE_H
