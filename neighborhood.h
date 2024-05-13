#ifndef NEIGHBORHOOD_H
#define NEIGHBORHOOD_H

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

class Neighborhood {
    public:
        Neighborhood();

        const std::unordered_set<std::string>& get_phases() const;
};

#endif
