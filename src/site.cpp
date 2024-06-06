#include "site.h"
#include "helpers.h"


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
    std::cout << "Site(arma::vec _location, std::string _site_class, int _site_id, int state)" << std::endl;
    this->_location = location;
    this->_site_class = site_class;
    this->_site_id = site_id;
    this->_state = state;
}

void Site::set_site_state(int state) {
    std::cout << "Site::set_site_state(int state)" << std::endl;
    this->_state = state;
}

const int Site::get_site_state() const {
    std::cout << "Site::get_site_state() const" << std::endl;
    return this->_state;
}

const int Site::get_site_id() const {
    std::cout << "Site::get_site_id() const" << std::endl;
    return this->_site_id;
}

const arma::vec Site::get_location() const {
    return this->_location;
}

const std::string Site::get_site_class() const {
    return this->_site_class;
}

const std::string Site::to_json() const {
        std::ostringstream oss;
        oss << "{";
        oss << "\"_location\": " << vec_to_json_string(_location) << ", ";
        oss << "\"_site_class\": \"" << _site_class << "\", ";
        oss << "\"_site_id\": " << _site_id;
        oss << "}";
        return oss.str();
}    