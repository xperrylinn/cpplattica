#include "moore_neighborhood_builder.h"
#include "helpers.h"
#include "euclidean_distance_map.h"

// MooreNeighborhoodBuilder::MooreNeighborhoodBuilder() {
//     std::cout << "MooreNeighborhoodBuilder::MooreNeighborhoodBuilder()" << std::endl;
// }

MooreNeighborhoodBuilder::MooreNeighborhoodBuilder(int size, int dim) 
: MotifNeighborhoodBuilder(get_points_in_cube(-1 * size, size + 1, dim))
 {
    std::cout << "MooreNeighborhoodBuilder::MooreNeighborhoodBuilder(int size, int dim)" << std::endl;
    // this->_motif(get_points_in_cube(-1 * size, size + 1, dim));
    this->distances = EuclideanDistanceMap(this->_motif);
}