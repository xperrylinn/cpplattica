#ifndef PERIODIC_STRUCTURE_H
#define PERIODIC_STRUCTURE_H

#include <vector>
#include <cassert>
#include <cmath>
#include <armadillo>
#include <unordered_map>
#include <tuple>
#include "lattice.h"
#include "site.h"


class PeriodicStructure {
    public:
        Lattice lattice;
        int dim;
        std::vector<int> site_ids;
        static std::vector<double> vec_offset;


        PeriodicStructure();
        PeriodicStructure(Lattice lattice);

        static PeriodicStructure build_from(
            Lattice lattice, 
            std::vector<int> num_cells, 
            std::unordered_map<std::string, arma::mat>& motif,
            const bool frac_coords = false
        );
        arma::vec _get_rounded_coords(const arma::vec& location);
        arma::vec _transformed_coords(const arma::vec& location);
        arma::vec _coords_with_offset(const arma::vec& location);
        int add_site(const std::string& site_class, const arma::vec& location);
        const std::vector<Site> sites() const;
        const std::vector<Site> sites(std::string site_class) const;
        const Site get_site(int site_id) const;
        const int id_at(arma::vec location) const;
        const Site site_at(arma::vec location) const;

        private:
            std::vector<Site> _sites;
            arma::vec _offset_vector;
            std::unordered_map<std::string, int> _location_lookup;

};

#endif
