#ifndef LATTICE_H
#define LATTICE_H

// #include <Eigen/Dense>
#include <vector>
#include <cassert>
#include <cmath>

class Lattice {
    public:
        Lattice(const std::vector<std::vector<double>>& vecs, bool periodic = true);

    private:

        std::vector<double> vecLengths;
        int dim;
        bool isPeriodic;
};

#endif // LATTICE_H
