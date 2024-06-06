#include <armadillo>
#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>
#include <iterator>
#include <algorithm>
#include <numeric>
#include "helpers.h"


TimePoint start_timer() {
    return Clock::now();
}

double stop_timer(const TimePoint& start) {
    TimePoint end = Clock::now();
    return std::chrono::duration<double>(end - start).count();
}

const std::string vec_to_hash_string(const arma::vec& vec) {
    std::cout << "vec_to_hash_string(const arma::vec& vec)" << std::endl;

    std::ostringstream oss;
    for (arma::uword i = 0; i < vec.n_elem; ++i) {
        if (i > 0) {
            oss << ",";
        }
        oss << vec(i);
    }
    
    return oss.str();
}

const std::string vec_to_json_string(const arma::vec& vec) {
    std::ostringstream oss;
    oss << "[";

    for (size_t i = 0; i < vec.n_elem; ++i) {
        oss << vec(i);
        if (i < vec.n_elem - 1) {
            oss << ", ";
        }
    }

    oss << "]";
    return oss.str();
}

std::string vecs_to_json_string(const std::vector<std::vector<double>>& vecs) {
    std::ostringstream oss;
    oss << "[";

    for (size_t i = 0; i < vecs.size(); ++i) {
        oss << "[";
        for (size_t j = 0; j < vecs[i].size(); ++j) {
            oss << vecs[i][j];
            if (j < vecs[i].size() - 1) {
                oss << ", ";
            }
        }
        oss << "]";
        if (i < vecs.size() - 1) {
            oss << ", ";
        }
    }

    oss << "]";
    return oss.str();
}

arma::mat get_points_in_box(const std::vector<int>& lbs, const std::vector<int>& ubs) {
    std::cout << "get_points_in_box(const std::vector<int>& lbs, const std::vector<int>& ubs)" << std::endl;

    // std::vector<int> x(10);
    // std::iota(std::begin(x), std::end(x), 0); //0 is the starting number

    std::vector<std::tuple<int, int>> zipped_args = zip(lbs, ubs);
    
    std::vector<std::vector<int>> int_ranges;
    for (const auto& tuple : zipped_args) {
        std::vector<int> int_range(std::get<1>(tuple) - std::get<0>(tuple));
        std::iota(std::begin(int_range), std::end(int_range), std::get<0>(tuple));
        int_ranges.push_back(int_range);
    }

    std::vector<std::vector<int>> int_cartesian_product = cartesian_product(int_ranges);

    arma::mat result(convert_to_arma_mat(int_cartesian_product));
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

std::vector<std::vector<int>> cartesian_product(const std::vector<std::vector<int>>& lists) {
    std::cout << "cartesian_product(const std::vector<std::vector<int>>& lists)" << std::endl;
    // Initialize the result with an empty product
    std::vector<std::vector<int>> result = {{}};

    // Iterate over each list in the input vector of vectors
    for (const auto& list : lists) {
        std::vector<std::vector<int>> temp;

        // Iterate over each partial product in the current result
        for (const auto& res : result) {
            // Append each element of the current list to the partial product
            for (int element : list) {
                std::vector<int> new_combination = res;
                new_combination.push_back(element);
                temp.push_back(new_combination);
            }
        }

        // Update the result with the new combinations
        result = temp;
    }

    return result;
}

arma::mat convert_to_arma_mat(const std::vector<std::vector<int>>& int_vec) {
    // Get the dimensions of the input vector
    size_t rows = int_vec.size();
    size_t cols = rows > 0 ? int_vec[0].size() : 0;

    // Create an arma::mat with the same dimensions, initialized to zeros
    arma::mat result(rows, cols, arma::fill::zeros);

    // Copy and convert elements from int to double
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result(i, j) = static_cast<double>(int_vec[i][j]);
        }
    }

    return result;
}

void write_string_to_file(const std::string& filename, const std::string& content) {
    std::ofstream outfile(filename);

    if (!outfile) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }

    outfile << content;

    outfile.close();

    if (!outfile.fail()) {
        std::cout << "File " << filename << " written successfully." << std::endl;
    } else {
        std::cerr << "Error: Could not write to file " << filename << "." << std::endl;
    }
}
