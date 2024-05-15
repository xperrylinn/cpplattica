#include <armadillo>
#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>
#include <iterator>
#include <algorithm>
#include "helpers.h"


std::string vec_to_string(const arma::vec& vec) {
    std::ostringstream oss;
    for (arma::uword i = 0; i < vec.n_elem; ++i) {
        if (i > 0) {
            oss << ",";
        }
        oss << vec(i);
    }
    return oss.str();
}

arma::mat get_points_in_box(const std::vector<int>& lbs, const std::vector<int>& ubs) {
    std::cout << "get_points_in_box(const std::vector<int>& lbs, const std::vector<int>& ubs)" << std::endl;

    // Calculate the number of dimensions
    size_t dim = lbs.size();

    // Compute the total number of points
    size_t total_points = 1;
    for (size_t i = 0; i < dim; ++i) {
        total_points *= (ubs[i] - lbs[i]);
    }

    // Create the result matrix
    arma::mat result(dim, total_points);

    // Initialize the index vector
    std::vector<size_t> index(dim, 0);

    // Populate the result matrix
    for (size_t i = 0; i < total_points; ++i) {
        // Set the current point
        for (size_t j = 0; j < dim; ++j) {
            result(j, i) = lbs[j] + index[j];
        }

        // Update the index for the next point
        for (size_t j = 0; j < dim; ++j) {
            index[j]++;
            if (index[j] < static_cast<size_t>(ubs[j] - lbs[j])) {
                break;
            }
            index[j] = 0;
        }
    }

    return result;
}

arma::mat get_points_in_cube(int lb, int ub, int dim) {
    std::cout << "get_points_in_cube(int lb, int ub, int dim)" << std::endl;
    std::vector<int> ubs(dim, ub);
    std::vector<int> lbs(dim, lb);
    arma::mat result(get_points_in_box(lbs, ubs));
    return result;
}

double distance(arma::vec p1, arma::vec p2) {
    std::cout << "distance(arma::vec p1, arma::vec p2)" << std::endl;
    double result = arma::norm(p1 - p2);
    return result;
}
