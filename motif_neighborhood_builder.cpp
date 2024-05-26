#include "motif_neighborhood_builder.h"


MotifNeighborhoodBuilder::MotifNeighborhoodBuilder(arma::mat motif) : _motif(motif) {
    std::cout << "MotifNeighborhoodBuilder::MotifNeighborhoodBuilder(arma::mat motif)" << std::endl;
}

std::vector<int> MotifNeighborhoodBuilder::get_neighbors(Site curr_site, PeriodicStructure structure) {
    std::cout << "MotifNeighborhoodBuilder::get_neighbors(int site_id, PeriodicStructure structure)" << std::endl;
    // location = curr_site[LOCATION]
    arma::vec location = curr_site.get_location();
    // nbs = []
    std::vector<int> neighbhors;
    // for neighbor_vec in self._motif:
    //     loc = tuple(s + n for s, n in zip(location, neighbor_vec))
    //     nb_id = struct.id_at(loc)
    //     if nb_id != curr_site[SITE_ID]:
    //         nbs.append((nb_id, self.distances.get_dist(neighbor_vec)))
    for (int i = 0; i < this->_motif.n_cols; i += 1) {
        arma::vec neighbor_vec = this->_motif.col(i);
        // std::vector<std::tuple<T, U>> zip(const std::vector<T>& vec1, const std::vector<U>& vec2)
    }
    return neighbhors;
}
