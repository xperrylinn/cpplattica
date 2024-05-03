#include <armadillo>
#include <tuple>
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
            std::unordered_map<std::string, arma::mat>& motif,
            const bool frac_coords
) {
    Lattice new_lattice = lattice.get_scaled_lattice(num_cells);
    PeriodicStructure structure(new_lattice);

    std::vector<int> zero_vector(new_lattice.dim, 0);
    arma::mat points = get_points_in_box(zero_vector, num_cells);

    std::cout << "points" << std::endl;
    std::cout << points << std::endl;
    if (!frac_coords) {
        points = lattice.mat * points;
    }

    std::cout << "lattice.mat" << std::endl;
    std::cout << lattice.mat << std::endl;

    std::cout << "points" << std::endl;
    std::cout << points << std::endl;

    for (int i = 0; i < points.n_cols; i += 1) {
        arma::vec point = points.col(i);

        std::cout << "point" << std::endl;
        std::cout << point << std::endl;

        for (const auto& pair : motif) {
            std::string site_class = pair.first;
            arma::mat basis_vecs = pair.second;

            std::cout << "basis_vecs" << std::endl;
            std::cout << basis_vecs << std::endl;

            for (int i = 0; i < basis_vecs.n_rows; i += 1) {
                arma::vec basis_vec = basis_vecs.row(i).t();
                
                std::cout << "basis_vec" << std::endl;
                std::cout << basis_vec << std::endl;
                
                arma::mat site_loc = point + basis_vec;
                
                std::cout << "site_loc" << std::endl;
                std::cout << site_loc << std::endl;

                std::tuple<int, int> coordinate = std::make_tuple(site_loc[0], site_loc[1]);

                if (frac_coords) {
                    throw std::invalid_argument("Logic not for frac_coords==true");
                }

                structure.add_site(site_class, coordinate);
            }
        }
    }
}

int PeriodicStructure::add_site(std::string site_class, std::tuple<int, int> coordinate) {
    return 0;
}
