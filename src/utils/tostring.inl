#pragma once 

#include <sstream>

// doesnt compile with vs!
template<typename T>
std::string toString(const glm::detail::tvec3<T> &v) {
#ifdef __linux__
    std::stringstream result;

    result << "(" << (float)v.x << "/" << (float)v.y << "/" << (float)v.z << ")";

    return result.str();
#else
    return "<util/toString is not available under windows>";
#endif
}


template<typename T>
std::string toString(const TAABB<T> &aabb) {
#ifdef __linux__
    std::stringstream result;

    result << "[" << toString(aabb.llf()) << " -> " << toString(aabb.rub()) << "]";

    return result.str();
#else
    return "<util/toString is not available under windows>";
#endif

}


