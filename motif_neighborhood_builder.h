#ifndef MOTIFNEIGHBORHOODBBUILDER_H
#define MOTIFNEIGHBORHOODBBUILDER_H
#include <armadillo>
#include "neighborhood_builder.h"
#include "euclidean_distance_map.h"
#include "periodic_structure.h"


class MotifNeighborhoodBuilder : public NeighborhoodBuilder {
    public:
        EuclideanDistanceMap distances;
    
        MotifNeighborhoodBuilder(arma::mat motif);
        std::vector<int> get_neighbors(int site_id, PeriodicStructure structure);
    protected:
        arma::mat _motif;
        
};

#endif
