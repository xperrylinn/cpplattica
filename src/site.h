#ifndef SITE_H
#define SITE_H

#include <vector>
#include <cassert>
#include <cmath>
#include <armadillo>
#include <string>


class Site {
    public:
        Site();

        Site(
            arma::vec location,
            std::string site_class,
            int site_id,
            int state
        );

        const int get_site_id() const;
        const int get_site_state() const;
        const std::string get_site_class() const;
        const int get_site_rank() const;
        void set_site_state(int state);
        void set_site_rank(int rank);
        const arma::vec get_location() const;
        const std::string to_json() const;

    private:
        arma::vec _location;
        std::string _site_class;
        int _site_id;
        int _state;
        int _rank;
};

#endif
