#include "motif_neighborhood_builder.h"


MotifNeighborhoodBuilder::MotifNeighborhoodBuilder(arma::mat motif) : _motif(motif) {
    std::cout << "MotifNeighborhoodBuilder::MotifNeighborhoodBuilder(arma::mat motif)" << std::endl;
}

std::vector<int> MotifNeighborhoodBuilder::get_neighbors(int site_id, PeriodicStructure structure) {
    // location = curr_site[LOCATION]
    Site curr_site = structure.get_site(site_id);
    // nbs = []
    std::vector<int> neighbhors;
    // for neighbor_vec in self._motif:
    for (int i = 0; i < this->_motif.n_cols; i += 1) {
        arma::vec loc = this->_motif.col(i);
    }
    //     loc = tuple(s + n for s, n in zip(location, neighbor_vec))
    //     nb_id = struct.id_at(loc)
    //     if nb_id != curr_site[SITE_ID]:
    //         nbs.append((nb_id, self.distances.get_dist(neighbor_vec)))
    return neighbhors;
}
