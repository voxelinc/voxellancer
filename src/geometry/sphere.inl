#pragma once

#include "aabb.h"


template<typename T>
bool Sphere::nearTo(const TAABB<T>& aabb) const {
    Sphere aabbSphere = Sphere::containing(aabb);
    return intersects(aabbSphere);
}


template<typename T>
Sphere Sphere::containing(const TAABB<T>& aabb) {
    Sphere result;

    result.setPosition(aabb.middle());
    result.setRadius(glm::length((aabb.rub() - aabb.llf()) / static_cast<T>(2)));

    return result;
}

