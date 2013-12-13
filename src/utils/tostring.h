#pragma once

#include <string>

#include <glm/glm.hpp>

#include "geometry/aabb.h"
#include "geometry/sphere.h"


template<typename T>
std::string toString(const glm::detail::tvec3<T>& v);

template<typename T>
std::string toString(const TAABB<T>& aabb);

std::string toString(const Sphere& sphere);


#include "tostring.inl"
