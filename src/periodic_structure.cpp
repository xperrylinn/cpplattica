#include <armadillo>
#include <tuple>
#include <sstream>
#include <unordered_map>
#include "periodic_structure.h"
#include "lattice.h"
#include "periodic_structure.h"
#include "helpers.h"
#include "constants.h"
#include "site.h"


PeriodicStructure::PeriodicStructure() {
    this->lattice = Lattice();
    this->dim = -1;
    this->_sites = {};
    this->site_ids = {};
    this->_offset_vector = {};
    this->_location_lookup = {};
    this->_site_id_rank_map = {};
}

PeriodicStructure::PeriodicStructure(Lattice lattice, int num_procs, int rank) {
    this->lattice = lattice;
    this->dim = lattice.dim;
    this->_sites = {};
    this->site_ids = {};
    this->_offset_vector = arma::vec(this->dim, arma::fill::value(VEC_OFFSET));
    this->_location_lookup = {};
    this->_site_id_rank_map = {};
    this->_num_procs = num_procs;
    this->_rank = rank;
}

const int PeriodicStructure::get_site_rank(int site_id) const {
    // std::cout << "PeriodicStructure::get_site_rank(int site_id)" << std::endl;
    return 0;
}

const int PeriodicStructure::get_num_procs() const {
    // std::cout << "PeriodicStructure::get_num_procs()" << std::endl;
    return this->_num_procs;
}

const int PeriodicStructure::get_rank() const {
    // std::cout << "PeriodicStructure::get_num_procs()" << std::endl;
    return this->_rank;
}

PeriodicStructure PeriodicStructure::build_from(
            Lattice lattice, 
            std::vector<int> num_cells, 
            std::unordered_map<std::string, arma::mat>& motif,
            int num_procs,
            int rank,
            const bool frac_coords
) {
    // // std::cout << "PeriodicStructure::build_from(Lattice lattice, std::vector<int> num_cells, std::unordered_map<std::string, arma::mat>& motif, const bool frac_coords)" << std::endl;
    Lattice new_lattice = lattice.get_scaled_lattice(num_cells);
    PeriodicStructure structure(new_lattice, num_procs, rank);

    std::vector<int> zero_vector(new_lattice.dim, 0);
    arma::mat points(get_points_in_box(zero_vector, num_cells));

    if (!frac_coords) {
        points = lattice.get_matrix() * points.t();
    }

    // Assign each site to a rank
    structure._site_id_rank_map.reserve(structure.get_num_sites());
    int starting_row = 0;
    int grid_dimension = ceil(structure.lattice.vec_lengths[0]);
    std::cout << "hi: " << grid_dimension << std::endl;
    std::cout << "structure._num_procs: " << structure.get_num_procs() << std::endl;
    std::cout << "structure._rank: " << structure.get_rank() << std::endl;
    for (int k = 0; k < num_procs; k += 1) {
        std::cout << "hi" << std::endl;
        int rows_assigned_to_rank = grid_dimension / num_procs; // int division
        if ((grid_dimension % num_procs) > k ) { //n rows leftover, assign to first n ranks
            rows_assigned_to_rank += 1;
        }

        for (int i = 0; i < rows_assigned_to_rank; i++) {
            std::cout << "hi2" << std::endl;
            for (int j = 0; j < grid_dimension; j++) {
                int curr_site_id = (i + starting_row) * grid_dimension + j;
                structure._site_id_rank_map[curr_site_id] = k;
                std::cout << "structure._site_id_rank_map[curr_site_id]: " << structure._site_id_rank_map[curr_site_id] << std::endl;
                if (rank == k) {
                    structure.rank_site_ids.push_back(curr_site_id);
                }
            }
        }
        print_unordered_map(structure._site_id_rank_map);
        starting_row += rows_assigned_to_rank; // incrementing for next rank's iteration 
    }

    for (int i = 0; i < points.n_cols; i += 1) {
        arma::vec point = points.col(i);

        for (const auto& pair : motif) {
            std::string site_class = pair.first;
            arma::mat basis_vecs = pair.second;

            for (int i = 0; i < basis_vecs.n_rows; i += 1) {
                arma::vec basis_vec = basis_vecs.row(i).t();
                arma::mat site_loc = point + basis_vec;

                if (frac_coords) {
                    throw std::invalid_argument("Logic not for frac_coords==true");
                }
                
                structure.add_site(site_class, site_loc);
            }
        }
    }

    return structure;
}

arma::vec PeriodicStructure::_coords_with_offset(const arma::vec& location) const {
    // std::cout << "PeriodicStructure::_coords_with_offset(const arma::vec& location)" << std::endl;
    return this->_get_rounded_coords(location + this->_offset_vector);
}

arma::vec PeriodicStructure::_get_rounded_coords(const arma::vec& location) const {
    // std::cout << "PeriodicStructure::_get_rounded_coords(const arma::vec& location)" << std::endl;
    double scale = std::pow(10.0, OFFSET_PRECISION);
    arma::vec rounded_coords = arma::round(location * scale) / scale;
    return rounded_coords;
}

arma::vec PeriodicStructure::_transformed_coords(const arma::vec& location) const {
    // std::cout << "PeriodicStructure::_transformed_coords(const arma::vec& location)" << std::endl;
    arma::vec periodized_coords = this->lattice.get_periodized_cartesian_coords(location);
    arma::vec offset_periodized_coords = this->_coords_with_offset(periodized_coords);
    return offset_periodized_coords;
}

int PeriodicStructure::add_site(const std::string& site_class, const arma::vec& location) {
    // std::cout << "PeriodicStructure::add_site(const std::string& site_class, const arma::vec& location)" << std::endl;
    int new_site_id = this->_sites.size();
    
    arma::vec periodized_coords = _get_rounded_coords(
            this->lattice.get_periodized_cartesian_coords(location)
    );

    arma::vec offset_periodized_coords = this->_transformed_coords(location);

    if (new_site_id > this->_sites.size()) {
        throw std::runtime_error("Error - attempeted too add site with an id that already exisits!");
    }

    Site new_site(
        location,
        site_class,
        new_site_id,
        -1
    );

    new_site.set_site_rank(this->_site_id_rank_map[new_site_id]);

    this->_sites.push_back(new_site);
    std::string vec_string = vec_to_hash_string(offset_periodized_coords);
    this->_location_lookup[vec_string] = new_site_id;
    this->site_ids.push_back(new_site_id);

    return new_site_id;
}

const std::vector<Site> PeriodicStructure::sites() const {
    // std::cout << "PeriodicStructure::sites() const" << std::endl;
    return this->_sites;
}

const Site PeriodicStructure::get_site(int site_id) const {
    // std::cout << "PeriodicStructure::get_site(int site_id) const" << std::endl;
    return this->_sites[site_id];
}

const int PeriodicStructure::get_num_sites() const {
    return this->_sites.size();
}

const int PeriodicStructure::id_at(arma::vec location) const {
    // std::cout << "PeriodicStructure::id_at(arma::vec location) const" << std::endl;
    // site = self.site_at(location)
    // if site is None:
    //     return None
    // else:
    //     return site[SITE_ID]
    Site site = this->site_at(location);
    return site.get_site_id();
}

const Site PeriodicStructure::site_at(arma::vec location) const {
    // std::cout << "PeriodicStructure::site_at(arma::vec location) const" << std::endl;
    arma::vec _transformed_coords = this->_transformed_coords(location);
    std::string location_at_string = vec_to_hash_string(_transformed_coords);
    int site_id = this->_location_lookup.at(location_at_string);
    return this->get_site(site_id);
}

const std::string PeriodicStructure::to_json() const {
    // std::cout << "PeriodicStructure::to_json()" << std::endl;

    std::ostringstream _sites_val;
    _sites_val << " {";
    for (int i = 0; i < this->get_num_sites(); i += 1) {
        _sites_val << "\"" << i << "\": ";
        Site site = this->_sites[i];
        _sites_val << site.to_json();
        if (i < this->get_num_sites() - 1) {
            _sites_val << ", ";
        }
    }
    _sites_val << "}";

    std::ostringstream result;
    result << "{\"lattice\": " << this->lattice.to_json() << ", \"_sites\": " << _sites_val.str() << "}";
    return result.str();
}
