#include <cmath>
#include "euclidean_distance_map.h"
#include "distance_map.h"
#include "helpers.h"


EuclideanDistanceMap::EuclideanDistanceMap() {}

EuclideanDistanceMap::EuclideanDistanceMap(arma::mat motif) {
    std::cout << "EuclideanDistanceMap::EuclideanDistanceMap(arma::mat motif)" << std::endl;
    this->distances = this->_find_distances(motif);
}

double EuclideanDistanceMap::_distance(arma::vec p1, arma::vec p2) {
    std::cout << "EuclideanDistanceMap::_distance(arma::vec p1, arma::vec p2)" << std::endl;
    double dist = distance(p1, p2);
    double rounded_dist = std::round(dist * 100.0) / 100.0;
    return rounded_dist;
}
