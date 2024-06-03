#include <vector>
#include "square_grid_lattice_2d.h"
#include "lattice.h"


SquareGridLattice2D::SquareGridLattice2D() {}

SquareGridLattice2D::SquareGridLattice2D(std::vector<std::vector<double>> lattice_vecs) : Lattice(lattice_vecs) {}