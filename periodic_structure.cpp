#include "periodic_structure.h"
#include "lattice.h"
#include "periodic_structure.h"
#include "helpers.h"


PeriodicStructure::PeriodicStructure() {}

PeriodicStructure::PeriodicStructure(Lattice lattice) {

}

PeriodicStructure PeriodicStructure::build_from(
            Lattice lattice, 
            std::vector<int> num_cells, 
            std::unordered_map<std::string, std::vector<std::vector<int>>>& motif,
            const bool frac_coords
) {
    Lattice new_lattice = lattice.get_scaled_lattice(num_cells);
    PeriodicStructure structure(new_lattice);

    std::vector<int> zero_vector(new_lattice.dim, 0);
    std::vector<std::vector<int>> vec_coeffs = get_points_in_box(zero_vector, num_cells);

}
