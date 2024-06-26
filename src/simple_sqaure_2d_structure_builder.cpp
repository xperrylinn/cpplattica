#include <vector>
#include <cassert>
#include <cmath>
#include <armadillo>
#include "structure_builder.h"
#include "square_grid_lattice_2d.h"
#include "simple_sqaure_2d_structure_builder.h"
#include "periodic_structure.h"


std::string SimpleSquare2DStructureBuilder::site_class = "_A";

SimpleSquare2DStructureBuilder::SimpleSquare2DStructureBuilder() {
    static std::string site_class;
    SquareGridLattice2D lattice;
    std::unordered_map<std::string, arma::mat> motif;
}

SimpleSquare2DStructureBuilder::SimpleSquare2DStructureBuilder(
    Lattice& lattice, 
    const std::unordered_map<std::string, arma::mat>& motif
) : StructureBuilder(lattice, motif) {

}

PeriodicStructure SimpleSquare2DStructureBuilder::build(int size, int num_procs, int rank) {
    std::vector<int> size_vector;
    // std::cout << "this->lattice.dim " << this->lattice.dim << std::endl;
    for (int i = 0; i < this->lattice.dim; i += 1) {
        size_vector.push_back(size);
    }
    PeriodicStructure periodic_structure = PeriodicStructure::build_from(
        this->lattice, 
        size_vector, 
        this->motif, 
        this->frac_coords,
        num_procs,
        rank
    );
    return periodic_structure;
}