#include "distance_map.h"
#include "helpers.h"


DistanceMap::DistanceMap() {}

std::unordered_map<std::string, double> DistanceMap::_find_distances(arma::mat relative_neighbor_locs) {
    std::unordered_map<std::string, double> result;
    for (int i = 0; i < relative_neighbor_locs.n_cols; i += 1) {
        arma::vec loc = relative_neighbor_locs.col(i);
        arma::vec zero_vec;
        zero_vec.zeros();
        result[vec_to_hash_string(loc)] = this->_distance(zero_vec, loc);
    }
    return result;
}

double DistanceMap::_distance(arma::vec zero_vec, arma::vec loc) {
    // std::cout << "DistanceMap::_distance(arma::vec zero_vec, arma::vec loc)" << std::endl;
    return 0.0;
}
