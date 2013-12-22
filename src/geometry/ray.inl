#pragma once

#include "aabb.h"


template<typename T>
bool Ray::nearTo(const TAABB<T>& aabb) const {
    Sphere aabbSphere = Sphere::containing(aabb);
    return intersects(aabbSphere);
}
