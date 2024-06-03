#ifndef NEIGHBORHOODBUILDER_H
#define NEIGHBORHOODBUILDER_H
#include <string>
#include <vector>
#include "neighborhood.h"
#include "periodic_structure.h"
#include "site.h"


class NeighborhoodBuilder {
    public:
        Neighborhood get(PeriodicStructure structure, std::string site_class = "");
        virtual std::vector<int> get_neighbors(Site curr_site, PeriodicStructure structure);
};

#endif
