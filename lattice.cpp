#include "lattice.h"
#include "helpers.h"


Lattice::Lattice() {};

Lattice::Lattice(const std::vector<std::vector<double>>& vecs, bool periodic) {
    assert(!vecs.empty() && "Lattice vectors cannot be empty");
    
    this->periodic = {};
    for (const auto& vec : vecs) {
        this->periodic.push_back(true);
    }    

    Lattice(vecs, this->periodic);
}

Lattice::Lattice(const std::vector<std::vector<double>>& vecs, std::vector<bool> periodic) {
    assert(!vecs.empty() && "Lattice vectors cannot be empty");

    this->vecs = vecs;
    
    this->periodic = periodic;

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

Lattice Lattice::get_scaled_lattice(std::vector<int> num_cells) {
    std::vector<std::tuple<int, std::vector<double>>> zipped_vecs = zip(num_cells, this->vecs);
    std::vector<std::vector<double>> scaled_lattice_vecs;
    for (const auto& pair : zipped_vecs) {
        int num_cell = std::get<0>(pair);
        std::vector<double> ref_vec_to_scale = std::get<1>(pair);
        std::vector<double> scaled_vector(ref_vec_to_scale);
        for (int i = 0; i < scaled_vector.size(); i += 1) {
            scaled_vector[i] *= num_cell;
        }
        scaled_lattice_vecs.push_back(scaled_vector);
    }
    Lattice lattice(scaled_lattice_vecs, this->periodic);
    return lattice;
}
