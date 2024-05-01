#ifndef PERIODIC_STRUCTURE_H
#define PERIODIC_STRUCTURE_H

#include <vector>
#include <cassert>
#include <cmath>
#include <armadillo>
#include <unordered_map>
#include "lattice.h"
#include "site.h"


class PeriodicStructure {
    public:
        Lattice lattice;
        int dim;
        std::vector<int> site_ids;
        static std::vector<double> vec_offset;


        PeriodicStructure();
        PeriodicStructure(Lattice lattice);

        static PeriodicStructure build_from(
            Lattice lattice, 
            std::vector<int> num_cells, 
            std::unordered_map<std::string, std::vector<std::vector<int>>>& motif,
            const bool frac_coords    
        );
        // std::vector<std::unordered_map<>>

        private:
            std::vector<Site> _sites;
            std::vector<double> _offset_vector;

};

#endif
