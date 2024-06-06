#include <string>
#include "neighborhood_builder.h"
#include "periodic_structure.h"
#include "neighborhood.h"
#include "site.h"


Neighborhood NeighborhoodBuilder::get(PeriodicStructure structure, std::string site_class) {
    // // std::cout << "NeighborhoodBuilder::get(PeriodicStructure structure, std::string site_class)" << std::endl;
    
    std::unordered_map<int, std::vector<int>> graph;

    std::vector<Site> sites;
    if (site_class == "") {
        sites = structure.sites(); 
    } else {
        throw std::invalid_argument("Logic not for site_class!=\"\"");
    }

    for (const auto& curr_site : structure.sites()) {
        graph[curr_site.get_site_id()] = {};
    }

    for (const auto& curr_site: structure.sites()) {
        std::vector<int> neighbors = this->get_neighbors(curr_site, structure);
        for (const auto& curr_neighbor_id: neighbors) {
            graph[curr_site.get_site_id()].push_back(curr_neighbor_id);
        }
    }

    return Neighborhood(graph);
}

std::vector<int> NeighborhoodBuilder::get_neighbors(Site curr_site, PeriodicStructure structure) {
    // // std::cout << "NeighborhoodBuilder::get_neighbors(int site_id, PeriodicStructure structure)" << std::endl;
    return {};
}
