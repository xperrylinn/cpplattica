#ifndef NEIGHBORHOODBUILDER_H
#define NEIGHBORHOODBUILDER_H
#include <string>
#include <vector>
#include "neighborhood.h"
#include "periodic_structure.h"


class NeighborhoodBuilder {
    public:
        Neighborhood get(PeriodicStructure structure, std::string site_class = "");
        std::vector<int> get_neighbors(int site_id, PeriodicStructure structure);
};

#endif
