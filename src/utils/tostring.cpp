#include "tostring.h"



template<> std::string _toString<Sphere>(const Sphere& sphere) {
    std::stringstream result;

    result << "[" << toString(sphere.position()) << " -> " << sphere.radius() << "]";

    return result.str();
}

