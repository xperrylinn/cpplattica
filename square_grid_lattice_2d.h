#ifndef SQUARE_GRID_LATTICE_2D_H
#define SQUARE_GRID_LATTICE_2D_H

#include <vector>
#include <utility>  // For std::pair
#include "lattice.h"

class SquareGridLattice2D : public Lattice {
    public:
        std::vector<std::vector<double>> lattice_vecs;
        
        SquareGridLattice2D();
        SquareGridLattice2D(std::vector<std::vector<double>> lattice_vecs);
};

#endif // SQUARE_GRID_LATTICE_2D_H
