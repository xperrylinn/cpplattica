#ifndef PERIODIC_STRUCTURE_H
#define PERIODIC_STRUCTURE_H

#include <vector>
#include <cassert>
#include <cmath>
#include <armadillo>
#include <unordered_map>
#include "lattice.h"


class PeriodicStructure {
    public:
        int hello_world;
        
        PeriodicStructure();

        static PeriodicStructure build_from(
            Lattice lattice, 
            std::vector<int> num_cells, 
            std::unordered_map<std::string, std::vector<std::vector<int>>>& motif,
            const bool frac_coords    
        );
};

#endif
