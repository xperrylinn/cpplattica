#ifndef DISTANCEMAP_H
#define DISTANCEMAP_H
#include <armadillo>
#include <string>
#include <unordered_map>


class DistanceMap {
    public:
        std::unordered_map<std::string, double> distances;

        DistanceMap();
        DistanceMap(arma::mat relative_neighbor_locs);
        std::unordered_map<std::string, double> _find_distances(arma::mat relative_neighbor_locs);
        double _distance(arma::vec zero_vec, arma::vec loc);
};

#endif
