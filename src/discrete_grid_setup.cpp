#include <vector>
#include <unordered_map>
#include "discrete_grid_setup.h"
#include "simulation.h"
#include "periodic_structure.h"
#include "simulation_state.h"
#include "simple_sqaure_2d_structure_builder.h"


DiscreteGridSetup::DiscreteGridSetup(PhaseSet& phase_set, int dim) : phase_set(phase_set) {
    // std::cout << "DiscreteGridSetup::DiscreteGridSetup(PhaseSet& phase_set, int dim) : phase_set(phase_set)" << std::endl;
    if (dim == 2) {
        std::vector<std::vector<double>> lattice_vecs = {{0.0, 1.0}, {1.0, 0.0}};
        SquareGridLattice2D lattice(lattice_vecs);
        std::vector<std::vector<double>> site_position_vector = {{site_position, site_position}};
        arma::mat motif_mat = {{site_position, site_position}};
        std::unordered_map<std::string, arma::mat> motif;
        motif.reserve(1);
        motif[SimpleSquare2DStructureBuilder::site_class] = motif_mat;
        // this->_builder.reset(new SimpleSquare2DStructureBuilder(lattice, motif));
        this->_builder = SimpleSquare2DStructureBuilder(lattice, motif);
    } else {
        throw std::invalid_argument("Logic only implemented for dim = 2.");
    }
}

Simulation DiscreteGridSetup::setup_noise(PhaseSet& phase_set, int size, int num_procs, int rank) {
    // std::cout << "DiscreteGridSetup::setup_noise(PhaseSet& phase_set, int size)" << std::endl;
    PeriodicStructure structure = this->_builder.build(size, num_procs, rank);
    // state: SimulationState = self._build_blank_state(structure)
    SimulationState state = this->_build_blank_state(structure);
    for (const auto& site : structure.sites()) {
        int random_state = phase_set.get_uniform_random_state();
        state.set_site_state(site.get_site_id(), random_state);
    }
    Simulation simulation(state, structure);
    return simulation;
}

SimulationState DiscreteGridSetup::_build_blank_state(const PeriodicStructure& structure) {
    // std::cout << "DiscreteGridSetup::_build_blank_state(const PeriodicStructure& structure)" << std::endl;
    SimulationState state;
    for (const auto& site : structure.sites()) {
        state.set_site_state(site.get_site_id(), -1);
    }
    return state;
}