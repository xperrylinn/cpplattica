#ifndef HELPERS_H
#define HELPERS_H
#include <iostream>
#include <vector>
#include <tuple>
#include <iterator>
#include <algorithm>


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
std::vector<std::vector<T>> get_points_in_box(const std::vector<T>& lbs, const std::vector<T>& ubs) {
    std::vector<std::vector<T>> result;

    // Create a vector of vectors to store the ranges
    std::vector<std::vector<T>> args;
    for (size_t i = 0; i < lbs.size(); ++i) {
        std::vector<T> range(ubs[i] - lbs[i]);
        std::iota(range.begin(), range.end(), lbs[i]);
        args.push_back(range);
    }

    // Compute the Cartesian product
    for (const auto& vec : args) {
        if (result.empty()) {
            for (const auto& elem : vec) {
                result.push_back({elem});
            }
        } else {
            std::vector<std::vector<T>> temp;
            for (const auto& elem : vec) {
                for (auto& res : result) {
                    auto temp_res = res;
                    temp_res.push_back(elem);
                    temp.push_back(temp_res);
                }
            }
            result = temp;
        }
    }

    return result;
}


#endif