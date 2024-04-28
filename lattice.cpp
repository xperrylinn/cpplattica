#include "lattice.h"


Lattice::Lattice() {};

Lattice::Lattice(const std::vector<std::vector<double>>& vecs, bool periodic) {
    assert(!vecs.empty() && "Lattice vectors cannot be empty");

    this->vecs = vecs;
    
    this->periodic = {};
    for (const auto& vec : vecs) {
        this->periodic.push_back(true);
    }    

    this->mat = {
        {0.0, 1.0},
        {1.0, 0.0}
    };

    this->vec_lengths = {};
    for (const auto& vec : vecs) {
        arma::vec temp_vec(vec);
        double norm = arma::norm(temp_vec, 2);
        this->vec_lengths.push_back(norm);
    }

    this->dim = vecs.size();

}
