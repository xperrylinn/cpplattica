#include <vector>
#include <cassert>
#include <cmath>
#include <armadillo>
#include "structure_builder.h"
#include "square_grid_lattice_2d.h"
#include "simple_sqaure_2d_structure_builder.h"



std::string SimpleSquare2DStructureBuilder::site_class = "_A";


SimpleSquare2DStructureBuilder::SimpleSquare2DStructureBuilder() {
    this->lattice = SquareGridLattice2D();
    std::vector<std::vector<int>> site_position_vector = {{site_position, site_position}};
    std::unordered_map<std::string, std::vector<std::vector<int>>> temp;
    temp[site_class] = site_position_vector;
    this->motif = temp;
    StructureBuilder(this->lattice, this->motif);
}
