#ifndef SIMULATIONSTATE_H
#define SIMULATIONSTATE_H

#include <vector>
#include <cassert>
#include <cmath>
#include <armadillo>
#include <unordered_map>
#include "site.h"


class SimulationState {
    public:

        SimulationState();

        void set_site_state(int site_id, int state);

    private:
        std::unordered_map<int, Site> _sites;
};

#endif