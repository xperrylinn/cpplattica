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
        const int num_sites() const;
        const std::vector<int> get_site_ids() const;
        const int get_site_state(int site_id) const;
    private:
        std::unordered_map<int, int> _sites;
};

#endif