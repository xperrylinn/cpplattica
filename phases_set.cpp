#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include "phases_set.h"


PhaseSet::PhaseSet() {}

PhaseSet::PhaseSet(const std::vector<std::string>& phases) {
    for (const std::string& phase : phases) {
        phases_set.insert(phase);
    }

    int i = 0;
    for (const auto& phase : phases_set) {
        phases_map[i] = phase;
        i += 1;
    }
}

const std::unordered_set<std::string>& PhaseSet::get_phases() const {
    return phases_set;
}

const std::string PhaseSet::get_phase(int i) const {
    return phases_map.at(i);
}