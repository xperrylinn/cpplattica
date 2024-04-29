#ifndef HELPERS_H
#define HELPERS_H
#include <iostream>
#include <vector>
#include <tuple>


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

#endif