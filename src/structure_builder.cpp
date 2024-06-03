#include "structure_builder.h"
#include "lattice.h"
#include "helpers.h"
#include <vector>
#include <string>
#include <unordered_map>


bool StructureBuilder::frac_coords = false;

StructureBuilder::StructureBuilder() {}

StructureBuilder::StructureBuilder(
    Lattice& lattice, 
    const std::unordered_map<std::string, arma::mat>& motif
) {
    this->lattice = lattice;
    this->motif = motif;
}

PeriodicStructure StructureBuilder::build(int size) {
    std::vector<int> num_cells;
    for (int i = 0; i < this->lattice.dim; i += 1) {
        num_cells.push_back(size);
    }
    PeriodicStructure periodic_struc = PeriodicStructure::build_from(this->lattice, num_cells, this->motif, this->frac_coords);
    return periodic_struc;
}
