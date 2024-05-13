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

arma::mat get_points_in_box(const std::vector<int>& lbs, const std::vector<int>& ubs);

arma::mat get_points_in_cube(int lb, int ub, int dim);

double distance(arma::vec p1, arma::vec p2);

#endif
