#include "simulation_state.h"
#include "periodic_structure.h"


SimulationState::SimulationState() {
    std::cout << "SimulationState()" << std::endl;
    this->_sites = {};
}

void SimulationState::set_site_state(int site_id, int state) {
    std::cout << "SimulationState::set_site_state(int site_id, int state)" << std::endl;
    this->_sites[site_id] = state;
}

const int SimulationState::num_sites() const {
    return this->_sites.size();
}

const std::vector<int> SimulationState::get_site_ids() const {
    std::vector<int> site_ids;
    site_ids.reserve(this->_sites.size());
    for (const auto& pair : this->_sites) {
        site_ids.push_back(pair.first);
    }
    return site_ids;
}

const int SimulationState::get_site_state(int site_id) const {
    return this->_sites.at(site_id);
}
