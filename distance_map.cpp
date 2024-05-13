#include "distance_map.h"
#include "helpers.h"


DistanceMap::DistanceMap() {}

std::unordered_map<std::string, double> DistanceMap::_find_distances(arma::mat relative_neighbor_locs) {
    std::unordered_map<std::string, double> result;
    for (int i = 0; i < relative_neighbor_locs.n_cols; i += 1) {
        arma::vec loc = relative_neighbor_locs.col(i);
        arma::vec zero_vec;
        zero_vec.zeros();
        result[vec_to_string(loc)] = this->_distance(zero_vec, loc);
    }
    return {};
}

double DistanceMap::_distance(arma::vec zero_vec, arma::vec loc) {
    throw std::invalid_argument("Logic not for frac_coords==true");
    return 0.0;
}
