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
            arma::vec _location,
            std::string _site_class,
            int _site_id
        );

    private:
        arma::vec _location;
        std::string _site_class;
        int _site_id;
};

#endif
