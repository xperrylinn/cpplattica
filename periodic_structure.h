#ifndef PERIODIC_STRUCTURE_H
#define PERIODIC_STRUCTURE_H

#include <vector>
#include <cassert>
#include <cmath>
#include <armadillo>
#include <unordered_map>
#include <tuple>
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
            std::unordered_map<std::string, arma::mat>& motif,
            const bool frac_coords = false
        );
        int add_site(std::string site_class, std::tuple<int, int> coordinate);

        private:
            std::vector<Site> _sites;
            std::vector<double> _offset_vector;

};

#endif
