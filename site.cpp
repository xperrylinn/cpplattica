#include "site.h"


Site::Site() {
    std::cout << "Site()" << std::endl;
    this->_location = {};
    this->_site_class = "null_site_class";
    this->_site_id = -1;
}

Site::Site(
    arma::vec _location,
    std::string _site_class,
    int _site_id
) {
    std::cout << "Site(arma::vec _location, std::string _site_class, int _site_id)" << std::endl;
    this->_location = _location;
    this->_site_class = _site_class;
    this->_site_id = _site_id;
}
