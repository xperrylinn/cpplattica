#ifndef HELPERS_H
#define HELPERS_H
#include <armadillo>
#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>
#include <iterator>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>


using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<Clock>;

TimePoint start_timer();

double stop_timer(const TimePoint& start);

const std::string vec_to_hash_string(const arma::vec& vec);

const std::string vec_to_json_string(const arma::vec& vec);

std::string vecs_to_json_string(const std::vector<std::vector<double>>& vecs);

void write_string_to_file(const std::string& filename, const std::string& content);

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

template <typename K, typename V>
void print_unordered_map(const std::unordered_map<K, V>& map) {
    std::cout << "{\n";
    for (const auto& pair : map) {
        std::cout << "  [" << pair.first << "] = " << pair.second << ",\n";
    }
    std::cout << "}\n";
}

template <typename Map>
std::vector<typename Map::key_type> unordered_map_keys_to_vec(const Map& map) {
    std::vector<typename Map::key_type> keys;
    keys.reserve(map.size());  // Reserve enough space in the vector to avoid multiple reallocations
    for (const auto& pair : map) {
        keys.push_back(pair.first);
    }
    return keys;
}

template <typename T>
void print_unordered_set(const std::unordered_set<T>& uset) {
    std::cout << "{ ";
    for (const auto& elem : uset) {
        std::cout << elem << " ";
    }
    std::cout << "}" << std::endl;
}

template <typename T>
std::vector<std::vector<T>> merge_vectors(
    const std::vector<std::vector<T>>& vec1,
    const std::vector<std::vector<T>>& vec2) {

    // Check if the two vectors have the same size
    if (vec1.size() != vec2.size()) {
        throw std::invalid_argument("Vectors must be of the same size");
    }

    // Resultant vector to store merged results
    std::vector<std::vector<T>> result(vec1.size());

    // Iterate through both vectors and concatenate the inner vectors
    for (size_t i = 0; i < vec1.size(); ++i) {
        result[i] = vec1[i];  // Copy the first vector's inner vector
        result[i].insert(result[i].end(), vec2[i].begin(), vec2[i].end());  // Append the second vector's inner vector
    }

    return result;
}

arma::mat get_points_in_box(const std::vector<int>& lbs, const std::vector<int>& ubs);

arma::mat get_points_in_cube(int lb, int ub, int dim);

double distance(arma::vec p1, arma::vec p2);

std::vector<std::vector<int>> cartesian_product(const std::vector<std::vector<int>>& lists);

arma::mat convert_to_arma_mat(const std::vector<std::vector<int>>& int_vec);

#endif
