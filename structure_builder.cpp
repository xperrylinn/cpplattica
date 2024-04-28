#include "structure_builder.h"
#include "lattice.h"
#include <vector>
#include <string>
#include <unordered_map>


bool StructureBuilder::frac_coords = false;

StructureBuilder::StructureBuilder() {}

StructureBuilder::StructureBuilder(
    Lattice& lattice, 
    const std::unordered_map<std::string, std::vector<std::vector<int>>>& motif
) {
    this->lattice = lattice;
    this->motif = motif;
}