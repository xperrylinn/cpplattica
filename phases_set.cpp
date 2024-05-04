#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <cstdlib>
#include "phases_set.h"


PhaseSet::PhaseSet() {}

PhaseSet::PhaseSet(const std::vector<std::string>& phases) {
    for (const std::string& phase : phases) {
        this->phases_set.insert(phase);
    }

    this->num_states = this->phases_set.size();

    int i = 0;
    for (const auto& phase : phases_set) {
        this->phases_map[i] = phase;
        i += 1;
    }
}

const std::unordered_set<std::string>& PhaseSet::get_phases() const {
    return this->phases_set;
}

const std::string PhaseSet::get_phase(int i) const {
    return this->phases_map.at(i);
}

int PhaseSet::get_uniform_random_state() const {
    return rand() % this->num_states;
}
