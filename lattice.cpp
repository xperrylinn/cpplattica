#include "lattice.h"
#include "helpers.h"


arma::vec periodize(const arma::vec& frac_coords, const arma::vec& periodic) {
    std::cout << "periodize(arma::vec frac_coords, arma::vec periodic)" << std::endl;
    std::cout << "frac_coords" << std::endl;
    std::cout << frac_coords << std::endl;
    std::cout << "periodic" << std::endl;
    std::cout << periodic << std::endl;
    arma::vec result = frac_coords - arma::floor(frac_coords) % periodic;
    std::cout << "result" << std::endl;
    std::cout << result << std::endl;
    return result;
}

Lattice::Lattice() { 
    std::cout << "Lattice()" << std::endl;
    // this->periodic;
    // this->vecs;
    // this->mat;
    // this->_inv_matrix;
    // this->_matrix;
    // this->vec_lengths;
    // this->dim;
};

Lattice::Lattice(const std::vector<std::vector<double>>& vecs, bool periodic) {
    std::cout << "Lattice(const std::vector<std::vector<double>>& vecs, bool periodic)" << std::endl;

    this->periodic = arma::ones(vecs.size());

    this->vecs = vecs;
    
    arma::mat temp_mat(vecs.size(), vecs[0].size());
    for (int i = 0; i < vecs.size(); i += 1) {
        for (int j = 0; j < vecs[0].size(); j += 1) {
            temp_mat(i, j) = vecs[i][j];
        }
    }
    this->_matrix = temp_mat;

    this->_inv_matrix = this->_matrix.i();

    this->vec_lengths = {};
    for (const auto& vec : vecs) {
        arma::vec temp_vec(vec);
        double norm = arma::norm(temp_vec, 2);
        this->vec_lengths.push_back(norm);
    }

    this->dim = vecs.size();
}

Lattice::Lattice(const std::vector<std::vector<double>>& vecs, arma::vec periodic) {
    std::cout << "HELLO Lattice(const std::vector<std::vector<double>>& vecs, std::vector<bool> periodic)" << std::endl;
    assert(!vecs.empty() && "Lattice vectors cannot be empty");

    this->vecs = vecs;
    
    this->periodic = periodic;

    arma::mat temp_mat(vecs.size(), vecs[0].size());
    for (int i = 0; i < vecs.size(); i += 1) {
        for (int j = 0; j < vecs[0].size(); j += 1) {
            temp_mat(i, j) = vecs[i][j];
        }
    }
    this->_matrix = temp_mat;

    this->_inv_matrix = this->_matrix.i();
    this->_matrix = arma::mat(this->_matrix);

    this->vec_lengths = {};
    for (const auto& vec : vecs) {
        arma::vec temp_vec(vec);
        double norm = arma::norm(temp_vec, 2);
        this->vec_lengths.push_back(norm);
    }

    this->dim = vecs.size();
}


Lattice Lattice::get_scaled_lattice(const std::vector<int>& num_cells) {
    std::cout << "Lattice::get_scaled_lattice(std::vector<int> num_cells)" << std::endl;
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

arma::vec Lattice::get_cartesian_coords(const arma::vec& fractional_coords) {
    std::cout << "Lattice::get_cartesian_coords(const arma::vec& fractional_coords)" << std::endl;
    // return arma::vec(arma::dot(fractional_coords, this->_matrix));
    std::cout << "fractional_coords" << std::endl;
    std::cout << fractional_coords << std::endl;
    std::cout << "this->_inv_matrix" << std::endl;
    std::cout << this->_inv_matrix << std::endl;
    return arma::vec(this->_inv_matrix * fractional_coords);
}

arma::vec Lattice::get_fractional_coords(const arma::vec& cart_coords) {
    std::cout << "Lattice::get_fractional_coords(const arma::vec& cart_coords)" << std::endl;
    // return arma::vec(arma::dot(cart_coords, this->_inv_matrix));
    std::cout << "cart_coords" << std::endl;
    std::cout << cart_coords << std::endl;
    std::cout << "this->_inv_matrix" << std::endl;
    std::cout << this->_inv_matrix << std::endl;
    return arma::vec(this->_inv_matrix * cart_coords);
}

arma::vec Lattice::get_periodized_cartesian_coords(const arma::vec& cart_coords) {
    std::cout << "Lattice::get_periodized_cartesian_coords(const arma::vec& cart_coords)" << std::endl;
    arma::vec result = cart_coords;
    result = this->get_fractional_coords(result);
    return this->get_cartesian_coords(periodize(result, this->periodic));
}

arma::mat Lattice::get_matrix() const {
    return this->_matrix;
}

arma::mat Lattice::get_inverse_matrix() const {
    return this->_inv_matrix;
}
