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
        int rank;
        SimulationState();
        SimulationState(int rank);

        void set_site_state(int site_id, int state);
        const int num_sites() const;
        const std::vector<int> get_site_ids() const;
        const int get_site_state(int site_id) const;
        void add_rank_site_id(int site_id);
        const std::vector<int> get_rank_site_ids() const;
        const std::string to_json() const;
    private:
        std::unordered_map<int, int> _sites;
        std::vector<int> _rank_site_ids;
};

#endif