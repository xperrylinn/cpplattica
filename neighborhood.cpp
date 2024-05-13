#include <unordered_map>
#include <vector>

#include "neighborhood.h"


Neighborhood::Neighborhood(): _graph({}) {}

Neighborhood::Neighborhood(std::unordered_map<int, std::vector<int>> graph) {
    this->_graph = graph;
}

Neighborhood::Neighborhood(const Neighborhood& other) : _graph(other._graph) {}

Neighborhood& Neighborhood::operator=(const Neighborhood& other) {
    if (this != &other) {
        this->_graph = other._graph;
    }
    return *this;
}

const std::unordered_map<int, std::vector<int>>& Neighborhood::get_graph() {
    return this->_graph;
}