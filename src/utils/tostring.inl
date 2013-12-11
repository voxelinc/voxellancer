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

	glm::detail::tvec3<T> diff = aabb.rub() - aabb.llf();

    result << "[" << toString(aabb.llf()) << " " << diff.x << "x" << diff.y << "x" << diff.z << "]";

    return result.str();
}



