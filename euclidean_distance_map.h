#ifndef EUCLIDEANDISTANCEMAP_H
#define EUCLIDEANDISTANCEMAP_H
#include <armadillo>
#include "distance_map.h"


class EuclideanDistanceMap : public DistanceMap {
    public:
        EuclideanDistanceMap();
        EuclideanDistanceMap(arma::mat motif);
    private:
        double _distance(arma::vec p1, arma::vec p2);
};

#endif
