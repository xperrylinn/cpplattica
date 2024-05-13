#include "simulation_state.h"
#include "periodic_structure.h"


SimulationState::SimulationState() {
    std::cout << "SimulationState()" << std::endl;
    this->_sites = {};
}

void SimulationState::set_site_state(int site_id, int state) {
    this->_sites[site_id].set_site_state(state);
}

int SimulationState::num_sites() {
    this->_sites.size();
}
