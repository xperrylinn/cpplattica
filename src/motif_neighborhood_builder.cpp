#include "motif_neighborhood_builder.h"


MotifNeighborhoodBuilder::MotifNeighborhoodBuilder(arma::mat motif) : _motif(motif) {
    // std::cout << "MotifNeighborhoodBuilder::MotifNeighborhoodBuilder(arma::mat motif)" << std::endl;
}

std::vector<int> MotifNeighborhoodBuilder::get_neighbors(Site curr_site, PeriodicStructure structure) {
    // std::cout << "MotifNeighborhoodBuilder::get_neighbors(int site_id, PeriodicStructure structure)" << std::endl;
    arma::vec location = curr_site.get_location();
    std::vector<int> neighbors;
    neighbors.reserve(this->_motif.n_rows);
    for (int i = 0; i < this->_motif.n_rows; i += 1) {
        arma::vec neighbor_vec = this->_motif.row(i).t();
        neighbor_vec = location + neighbor_vec;
        int neighbor_id = structure.id_at(neighbor_vec);
        int curr_site_id = curr_site.get_site_id();
        if (neighbor_id != curr_site_id) {
            // std::cout << "curr_site.get_site_id(): " << curr_site_id << " neighbor_id: " << neighbor_id << std::endl;
            neighbors.push_back(neighbor_id);
        }
    }
    return neighbors;
}
