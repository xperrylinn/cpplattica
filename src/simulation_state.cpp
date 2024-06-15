#include "simulation_state.h"
#include "periodic_structure.h"
#include "helpers.h"


SimulationState::SimulationState() {
    // std::cout << "SimulationState()" << std::endl;
    this->_sites = {};
}

SimulationState::SimulationState(int rank) {
    // std::cout << "SimulationState()" << std::endl;
    this->rank = rank;
    this->_sites = {};
}

void SimulationState::set_site_state(int site_id, int state) {
    // std::cout << "SimulationState::set_site_state(int site_id, int state)" << std::endl;
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

const std::vector<int> SimulationState::get_rank_site_ids() const {
    std::cout << "SimulationState::get_rank_site_ids()" << std::endl;
    print_vector(this->_rank_site_ids);
    return this->_rank_site_ids;
}

void SimulationState::add_rank_site_id(int site_id) {
    // std::cout << "SimulationState::add_rank_site(int site_id)" << std::endl;
    this->_rank_site_ids.push_back(site_id);
}

const int SimulationState::get_site_state(int site_id) const {
    // std::cout << "SimulationState::get_site_state(int site_id)" << std::endl;
    return this->_sites.at(site_id);
}
