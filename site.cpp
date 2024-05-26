#include "site.h"


Site::Site() {
    std::cout << "Site()" << std::endl;
    this->_location = {};
    this->_site_class = "null_site_class";
    this->_site_id = -1;
    this->_state = -1;
}

Site::Site(
    arma::vec location,
    std::string site_class,
    int site_id,
    int state
) {
    std::cout << "Site(arma::vec _location, std::string _site_class, int _site_id)" << std::endl;
    this->_location = location;
    this->_site_class = site_class;
    this->_site_id = site_id;
    this->_state = state;
}

void Site::set_site_state(int state) {
    std::cout << "Site::set_site_state(int state)" << std::endl;
    this->_state = state;
}

int Site::site_id() const {
    std::cout << "Site::site_id()" << std::endl;
    return this->_site_id;
}

const arma::vec Site::get_location() const {
    return this->_location;
}
