#pragma once

#include "aabb.h"

template<typename T>
Sphere Sphere::containing(const TAABB<T>& aabb) {
    Sphere result;

    result.setPosition(glm::vec3(aabb.middle()));
    result.setRadius(glm::length((aabb.rub() - aabb.llf()) / static_cast<T>(2)));

    return result;
}

