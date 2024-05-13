#include "moore_neighborhood_builder.h"
#include "helpers.h"
#include "euclidean_distance_map.h"


MooreNeighborhoodBuilder::MooreNeighborhoodBuilder(int size, int dim) {
    this->_motif = get_points_in_cube(-1 * size, size + 1, dim);
    this->distances = EuclideanDistanceMap(this->_motif);
}