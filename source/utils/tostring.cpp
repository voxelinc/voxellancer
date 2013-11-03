#include "tostring.h"

#include <sstream>


std::string toString(const glm::vec3 &v) {
    std::stringstream result;

    result << "(" << v.x << "/" << v.y << "/" << v.z << ")";

    return result.str();
}

std::string toString(const AABB &aabb) {
    std::stringstream result;

    result << "[" << toString(aabb.llf()) << " -> " << toString(aabb.rub()) << "]";

    return result.str();
}
