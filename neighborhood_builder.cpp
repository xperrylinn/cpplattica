#include <string>
#include "neighborhood_builder.h"
#include "periodic_structure.h"
#include "neighborhood.h"
#include "site.h"


Neighborhood NeighborhoodBuilder::get(PeriodicStructure structure, std::string site_class) {
    std::cout << "NeighborhoodBuilder::get(PeriodicStructure structure, std::string site_class)" << std::endl;
    
    // graph = rx.PyDiGraph()
    std::unordered_map<int, std::vector<int>> graph;

    // if site_class is None:
    //     sites = struct.sites()
    // else:
    //     sites = struct.sites(site_class=site_class)
    std::vector<Site> sites;
    if (site_class == "") {
        sites = structure.sites(); 
    } else {
        throw std::invalid_argument("Logic not for site_class!=\"\"");
    }

    // for site in struct.sites():
    //     graph.add_node(site[SITE_ID])
    for (const auto& curr_site : structure.sites()) {
        graph[curr_site.site_id()] = {};
    }

    // for curr_site in tqdm(sites):
    //     nbs = self.get_neighbors(curr_site, struct)
    //     for nb_id, weight in nbs:
    //         graph.add_edge(curr_site[SITE_ID], nb_id, weight)
    for (const auto& curr_site: structure.sites()) {
        std::vector<int> neighbors = this->get_neighbors(curr_site, structure);
        for (const auto& curr_neighbor_id: neighbors) {
            graph[curr_neighbor_id].push_back(curr_neighbor_id);
        }
    }

    return Neighborhood(graph);
}

std::vector<int> NeighborhoodBuilder::get_neighbors(Site curr_site, PeriodicStructure structure) {
    std::cout << "NeighborhoodBuilder::get_neighbors(int site_id, PeriodicStructure structure)" << std::endl;
    return {};
}
