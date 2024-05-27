#include "motif_neighborhood_builder.h"


MotifNeighborhoodBuilder::MotifNeighborhoodBuilder(arma::mat motif) : _motif(motif) {
    std::cout << "MotifNeighborhoodBuilder::MotifNeighborhoodBuilder(arma::mat motif)" << std::endl;
}

std::vector<int> MotifNeighborhoodBuilder::get_neighbors(Site curr_site, PeriodicStructure structure) {
    std::cout << "MotifNeighborhoodBuilder::get_neighbors(int site_id, PeriodicStructure structure)" << std::endl;
    // location = curr_site[LOCATION]
    arma::vec location = curr_site.get_location();
    // nbs = []
    std::vector<int> neighbors;
    // for neighbor_vec in self._motif:
    //     loc = tuple(s + n for s, n in zip(location, neighbor_vec))
    //     nb_id = struct.id_at(loc)
    //     if nb_id != curr_site[SITE_ID]:
    //         nbs.append((nb_id, self.distances.get_dist(neighbor_vec)))
    // std::cout << "this->_motif" << this->_motif << std::endl;
    for (int i = 0; i < this->_motif.n_rows; i += 1) {
        arma::vec neighbor_vec = this->_motif.row(i).t();
        // std::cout << "location" << std::endl << location << std::endl;
        // std::cout << "neighbor_vec" << std::endl << neighbor_vec << std::endl;
        neighbor_vec = location + neighbor_vec;
        int neighbor_id = structure.id_at(neighbor_vec);
        if (neighbor_id != curr_site.get_site_id()) {
            neighbors.push_back(neighbor_id);
        }
    }
    return neighbors;
}
