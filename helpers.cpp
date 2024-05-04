#include <armadillo>
#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>
#include <iterator>
#include <algorithm>
#include "helpers.h"


std::string vec_to_string(const arma::vec& vec) {
    std::ostringstream oss;
    for (arma::uword i = 0; i < vec.n_elem; ++i) {
        if (i > 0) {
            oss << ",";
        }
        oss << vec(i);
    }
    return oss.str();
}
