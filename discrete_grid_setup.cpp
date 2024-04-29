#include "discrete_grid_setup.h"
#include "simulation.h"
#include "periodic_structure.h"


DiscreteGridSetup::DiscreteGridSetup(PhaseSet& phase_set, int dim) {
    if (dim == 2) {
        this->_builder = SimpleSquare2DStructureBuilder();
    } else {
        throw std::invalid_argument("Logic only implemented for dim = 2.");
    } 
    this->phase_set = phase_set;
}

Simulation DiscreteGridSetup::setup_noise(PhaseSet& phase_set, int size) {
    PeriodicStructure structure = this->_builder.build(size);
    
    return Simulation();
}
