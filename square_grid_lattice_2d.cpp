#include <vector>
#include "square_grid_lattice_2d.h"
#include "lattice.h"


SquareGridLattice2D::SquareGridLattice2D() {
    this->lattice_vecs = {{0.0, 1.0}, {1.0, 0.0}};
    Lattice(this->lattice_vecs);
}