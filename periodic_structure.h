#ifndef PERIODIC_STRUCTURE_H
#define PERIODIC_STRUCTURE_H

#include <vector>
#include <cassert>
#include <cmath>
#include <armadillo>


class PeriodicStructure {
    public:
        int hello_world;
        
        PeriodicStructure();

        static PeriodicStructure build_from();
};

#endif
