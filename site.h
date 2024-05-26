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

        int site_id() const;
        void set_site_state(int state);
        const arma::vec get_location() const;

    private:
        arma::vec _location;
        std::string _site_class;
        int _site_id;
        int _state;
};

#endif
