#ifndef LATTICE_H
#define LATTICE_H

// #include <Eigen/Dense>
#include <string>
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
        std::vector<double> vec_lengths;

        Lattice();
        Lattice(const std::vector<std::vector<double>>& vecs, bool periodic = true);
        Lattice(const std::vector<std::vector<double>>& vecs, arma::vec periodic);

        arma::vec get_cartesian_coords(const arma::vec& fractional_coords) const;
        Lattice get_scaled_lattice(const std::vector<int>& num_cells) const;
        arma::vec get_periodized_cartesian_coords(const arma::vec& cart_coords) const;
        arma::vec get_fractional_coords(const arma::vec& cart_coords) const;
        arma::mat get_matrix() const;
        arma::mat get_inverse_matrix() const;
        const std::string to_json() const;

    private:
        
        std::vector<bool> _periodic_bool;
        arma::mat _matrix;
        arma::mat _inv_matrix;
};

#endif // LATTICE_H
