#ifndef SIMPLESQUARE2DSTRUCTUREBUILDER_H
#define SIMPLESQUARE2DSTRUCTUREBUILDER_H

#include <vector>
#include <cassert>
#include <cmath>
#include <armadillo>
#include <string>
#include "structure_builder.h"
#include "square_grid_lattice_2d.h"

#define site_position 0


class SimpleSquare2DStructureBuilder : public StructureBuilder {
    public:
        static std::string site_class;
        SquareGridLattice2D lattice;
        std::unordered_map<std::string, std::vector<std::vector<int>>> motif;

        SimpleSquare2DStructureBuilder();
};

#endif // SIMPLESQUARE2DSTRUCTUREBUILDER_H