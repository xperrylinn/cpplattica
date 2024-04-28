#include "discrete_grid_setup.h"


DiscreteGridSetup::DiscreteGridSetup(PhaseSet& phase_set, int dim) {
    if (dim == 2) {
        this->_builder = SimpleSquare2DStructureBuilder();
    } else {
        throw std::invalid_argument("Logic only implemented for dim = 2.");
    } 
    this->phase_set = phase_set;
}