#ifndef MOORENBHOODBUILDER_H
#define MOORENBHOODBUILDER_H
#include "motif_neighborhood_builder.h"


class MooreNeighborhoodBuilder : public MotifNeighborhoodBuilder {
    public:
        // MooreNeighborhoodBuilder();
        MooreNeighborhoodBuilder(int size=1, int dim=2);
};

#endif
