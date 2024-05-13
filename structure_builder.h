#ifndef STRUCTUREBUILDER_H
#define STRUCTUREBUILDER_H

#include <vector>
#include <string>
#include <unordered_map>
#include "lattice.h"
#include "periodic_structure.h"


class StructureBuilder {
    public:
        static bool frac_coords;
        Lattice lattice;
        std::unordered_map<std::string, arma::mat> motif;

        StructureBuilder();
        StructureBuilder(Lattice& lattice, const std::unordered_map<std::string, arma::mat>& motif);
        PeriodicStructure build(int size);
};

#endif
