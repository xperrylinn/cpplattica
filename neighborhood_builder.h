#ifndef NEIGHBORHOODBUILDER_H
#define NEIGHBORHOODBUILDER_H
#include <string>
#include "neighborhood.h"
#include "periodic_structure.h"


class NeighborhoodBuilder {
    public:
        Neighborhood get(PeriodicStructure structure, std::string site_class = "");
};

#endif
