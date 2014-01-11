#pragma once

#include "aabb.h"

template<typename T>
Sphere Sphere::containing(const TAABB<T>& aabb) {
    Sphere result;

    result.setPosition(glm::vec3(aabb.middle()));
    result.setRadius((glm::length(glm::vec3(aabb.rub() - aabb.llf()) / 2.0f)));

    return result;
}

