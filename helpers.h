#ifndef HELPERS_H
#define HELPERS_H
#include <armadillo>
#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>
#include <iterator>
#include <algorithm>


std::string vec_to_string(const arma::vec& vec);

template<typename T, typename U>
std::vector<std::tuple<T, U>> zip(const std::vector<T>& vec1, const std::vector<U>& vec2) {
    std::vector<std::tuple<T, U>> result;
    auto size = std::min(vec1.size(), vec2.size());
    for (size_t i = 0; i < size; ++i) {
        result.emplace_back(vec1[i], vec2[i]);
    }
    return result;
}

template<typename T>
void print_vector(const std::vector<T>& vec) {
    std::cout << "[ ";
    for (const T& element : vec) {
        std::cout << element << " ";
    }
    std::cout << "]" << std::endl;
}

template<typename T>
arma::mat get_points_in_box(const std::vector<T>& lbs, const std::vector<T>& ubs) {
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

#endif
