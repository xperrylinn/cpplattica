#ifndef NEIGHBORHOOD_H
#define NEIGHBORHOOD_H

#include <vector>
#include <string>
#include <unordered_map>

class Neighborhood {
    public:
        Neighborhood();
        Neighborhood(std::unordered_map<int, std::vector<int>> graph);
        Neighborhood(const Neighborhood& other);
        Neighborhood& operator=(const Neighborhood& other);
        const std::unordered_map<int, std::vector<int>>& get_graph();

    private:
        std::unordered_map<int, std::vector<int>> _graph;
};

#endif
