#include "tostring.h"

#include <sstream>

// doesnt compile with vs!

std::string toString(const glm::vec3 &v) {
#ifdef __linux__
    std::stringstream result;

    result << "(" << v.x << "/" << v.y << "/" << v.z << ")";

    return result.str();
#else
    return "<util/toString is not available under windows>";
#endif
}

std::string toString1(const AABB &aabb) {
#ifdef __linux__
    std::stringstream result;

    result << "[" << toString1(aabb.llf()) << " -> " << toString1(aabb.rub()) << "]";

    return result.str();
#else
    return "<util/toString is not available under windows>";
#endif

}

