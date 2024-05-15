#ifndef MOTIFNEIGHBORHOODBBUILDER_H
#define MOTIFNEIGHBORHOODBBUILDER_H
#include <armadillo>
#include "neighborhood_builder.h"
#include "euclidean_distance_map.h"


class MotifNeighborhoodBuilder : public NeighborhoodBuilder {
    public:
        EuclideanDistanceMap distances;
    
        MotifNeighborhoodBuilder(arma::mat motif);
    protected:
        arma::mat _motif;
        
};

#endif
