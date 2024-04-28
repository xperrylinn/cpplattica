#ifndef STRUCTUREBUILDER_H
#define STRUCTUREBUILDER_H

#include <vector>
#include <string>
#include <unordered_map>
#include "lattice.h"


class StructureBuilder {
    public:
        static bool frac_coords;
        Lattice lattice;
        std::unordered_map<std::string, std::vector<std::vector<int>>> motif;

        StructureBuilder();

        StructureBuilder(Lattice& lattice, const std::unordered_map<std::string, std::vector<std::vector<int>>>& motif);
};

#endif // STRUCTUREBUILDER_H