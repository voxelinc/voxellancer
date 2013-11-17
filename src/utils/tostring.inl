#pragma once 

#include <sstream>

// doesnt compile with vs!
template<typename T>
std::string toString(const glm::detail::tvec3<T> &v) {
    std::stringstream result;

    result << "(" << (float)v.x << "/" << (float)v.y << "/" << (float)v.z << ")";

    return result.str();
}


template<typename T>
std::string toString(const TAABB<T> &aabb) {
    std::stringstream result;

    result << "[" << toString(aabb.llf()) << " -> " << toString(aabb.rub()) << "]";

    return result.str();
}


