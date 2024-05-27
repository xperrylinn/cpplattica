#include <armadillo>
#include <tuple>
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
}

PeriodicStructure::PeriodicStructure(Lattice lattice) {
    this->lattice = lattice;
    this->dim = lattice.dim;
    this->_sites = {};
    this->site_ids = {};
    this->_offset_vector = arma::vec(this->dim, arma::fill::value(VEC_OFFSET));
    this->_location_lookup = {};
}

PeriodicStructure PeriodicStructure::build_from(
            Lattice lattice, 
            std::vector<int> num_cells, 
            std::unordered_map<std::string, arma::mat>& motif,
            const bool frac_coords
) {
    std::cout << "PeriodicStructure::build_from(Lattice lattice, std::vector<int> num_cells, std::unordered_map<std::string, arma::mat>& motif, const bool frac_coords)" << std::endl;
    Lattice new_lattice = lattice.get_scaled_lattice(num_cells);
    PeriodicStructure structure(new_lattice);

    std::vector<int> zero_vector(new_lattice.dim, 0);
    arma::mat points(get_points_in_box(zero_vector, num_cells));

    // std::cout << "points" << std::endl;
    // std::cout << points << std::endl;
    if (!frac_coords) {
        points = lattice.get_matrix() * points.t();
    }

    // std::cout << "lattice.mat" << std::endl;
    // std::cout << lattice.get_matrix() << std::endl;

    // std::cout << "points" << std::endl;
    // std::cout << points << std::endl;

    for (int i = 0; i < points.n_cols; i += 1) {
        arma::vec point = points.col(i);

        // std::cout << "point" << std::endl;
        // std::cout << point << std::endl;

        for (const auto& pair : motif) {
            std::string site_class = pair.first;
            arma::mat basis_vecs = pair.second;

            // std::cout << "basis_vecs" << std::endl;
            // std::cout << basis_vecs << std::endl;

            for (int i = 0; i < basis_vecs.n_rows; i += 1) {
                arma::vec basis_vec = basis_vecs.row(i).t();
                
                // std::cout << "basis_vec" << std::endl;
                // std::cout << basis_vec << std::endl;
                
                arma::mat site_loc = point + basis_vec;
                
                // std::cout << "site_loc" << std::endl;
                // std::cout << site_loc << std::endl;

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
    std::cout << "PeriodicStructure::_coords_with_offset(const arma::vec& location)" << std::endl;
    return this->_get_rounded_coords(location + this->_offset_vector);
}

arma::vec PeriodicStructure::_get_rounded_coords(const arma::vec& location) const {
    std::cout << "PeriodicStructure::_get_rounded_coords(const arma::vec& location)" << std::endl;
    double scale = std::pow(10.0, OFFSET_PRECISION);
    arma::vec rounded_coords = arma::round(location * scale) / scale;
    // std::cout << "rounded_coords\n" << rounded_coords << std::endl;
    return rounded_coords;
}

arma::vec PeriodicStructure::_transformed_coords(const arma::vec& location) const {
    std::cout << "PeriodicStructure::_transformed_coords(const arma::vec& location)" << std::endl;
    arma::vec periodized_coords = this->lattice.get_periodized_cartesian_coords(location);
    // std::cout << "this->lattice.get_periodized_cartesian_coords(location)\n" << this->lattice.get_periodized_cartesian_coords(location) << std::endl;
    arma::vec offset_periodized_coords = this->_coords_with_offset(periodized_coords);
    // std::cout << "this->_coords_with_offset(periodized_coords)\n" << this->_coords_with_offset(periodized_coords) << std::endl;
    return offset_periodized_coords;
}

int PeriodicStructure::add_site(const std::string& site_class, const arma::vec& location) {
    std::cout << "PeriodicStructure::add_site(const std::string& site_class, const arma::vec& location)" << std::endl;
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
    this->_sites.push_back(new_site);
    std::string vec_string = vec_to_string(offset_periodized_coords);
    this->_location_lookup[vec_string] = new_site_id;
    this->site_ids.push_back(new_site_id);

    return new_site_id;
}

const std::vector<Site> PeriodicStructure::sites() const {
    std::cout << "PeriodicStructure::sites() const" << std::endl;
    return this->_sites;
}

const Site PeriodicStructure::get_site(int site_id) const {
    std::cout << "PeriodicStructure::get_site(int site_id) const" << std::endl;
    return this->_sites[site_id];
}

const int PeriodicStructure::id_at(arma::vec location) const {
    std::cout << "PeriodicStructure::id_at(arma::vec location) const" << std::endl;
    // site = self.site_at(location)
    // if site is None:
    //     return None
    // else:
    //     return site[SITE_ID]
    Site site = this->site_at(location);
    return site.get_site_id();
}

const Site PeriodicStructure::site_at(arma::vec location) const {
    std::cout << "PeriodicStructure::site_at(arma::vec location) const" << std::endl;
    // _transformed_coords = tuple(self._transformed_coords(location))
    arma::vec _transformed_coords = this->_transformed_coords(location);
    // site_id = self._location_lookup.get(_transformed_coords)
    std::string location_at_string = vec_to_string(_transformed_coords);
    int site_id = this->_location_lookup.at(location_at_string);

    // if site_id is not None:
    //     return self.get_site(site_id)
    // else:
    //     return None
    return this->get_site(site_id);
}
