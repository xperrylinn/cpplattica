#include "lattice.h"


Lattice::Lattice(const std::vector<std::vector<double>>& vecs, bool periodic)
{
    assert(!vecs.empty() && "Lattice vectors cannot be empty");
    dim = vecs[0].size();  // Assuming all vectors are of same dimension
}
