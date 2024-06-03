#ifndef PHASE_SET_H
#define PHASE_SET_H

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

class PhaseSet {
    public:
        PhaseSet();
        PhaseSet(const std::vector<std::string>& phases);

        const std::unordered_set<std::string>& get_phases() const;
        int get_uniform_random_state() const;
        const std::string get_phase(int i) const;
        

    private:
        int num_states;
        std::unordered_set<std::string> phases_set;
        std::unordered_map<int, std::string> phases_map;
};

#endif // PHASE_SET_H
