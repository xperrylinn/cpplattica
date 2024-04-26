#ifndef PHASE_SET_H
#define PHASE_SET_H

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

class PhaseSet {
public:
    // Constructor
    PhaseSet(const std::vector<std::string>& phases);

    // Accessor for the set of phases
    const std::unordered_set<std::string>& get_phases() const;

    // Accessor for individual phases based on an integer index
    const std::string get_phase(int i) const;

private:
    std::unordered_set<std::string> phases_set;
    std::unordered_map<int, std::string> phases_map;
};

#endif // PHASE_SET_H
