#ifndef DISCRETEGRIDSETUP_H
#define DISCRETEGRIDSETUP_H

#include <vector>
#include <string>
#include <unordered_map>
#include "simple_sqaure_2d_structure_builder.h"
#include "phases_set.h"
#include "simulation.h"
#include "simulation_state.h"


class DiscreteGridSetup {
    public:
        PhaseSet phase_set;
        DiscreteGridSetup(PhaseSet& phase_set, int dim = 2);
        Simulation setup_noise(PhaseSet& phase_set, int size);
    private:
        SimpleSquare2DStructureBuilder _builder;
        SimulationState _build_blank_state(PeriodicStructure structure);
};

#endif // DISCRETEGRIDSETUP_H
