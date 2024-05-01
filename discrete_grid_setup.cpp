#include <vector>
#include <unordered_map>
#include "discrete_grid_setup.h"
#include "simulation.h"
#include "periodic_structure.h"
#include "simulation_state.h"
#include "simple_sqaure_2d_structure_builder.h"


DiscreteGridSetup::DiscreteGridSetup(PhaseSet& phase_set, int dim) : phase_set(phase_set) {
// DiscreteGridSetup::DiscreteGridSetup(PhaseSet& phase_set, int dim) {
    if (dim == 2) {
        std::vector<std::vector<double>> lattice_vecs = {{0.0, 1.0}, {1.0, 0.0}};
        SquareGridLattice2D lattice(lattice_vecs);
        std::vector<std::vector<int>> site_position_vector = {{site_position, site_position}};
        std::unordered_map<std::string, std::vector<std::vector<int>>> motif;
        motif[SimpleSquare2DStructureBuilder::site_class] = site_position_vector;
        // this->_builder = SimpleSquare2DStructureBuilder(lattice, motif);
        this->_builder.reset(new SimpleSquare2DStructureBuilder(lattice, motif));
    } else {
        throw std::invalid_argument("Logic only implemented for dim = 2.");
    } 
    this->phase_set = phase_set; // not neded now that it's in initializer
}

Simulation DiscreteGridSetup::setup_noise(PhaseSet& phase_set, int size) {
    std::cout << "here?" << std::endl;
    PeriodicStructure structure = this->_builder->build(size);
    // SimulationState state = this->_build_blank_state(structure);

    return Simulation();
}

SimulationState DiscreteGridSetup::_build_blank_state(const PeriodicStructure& structure) {
    // SimulationState state;
    // for (const auto& site : structure.sites()) {

    // }
}