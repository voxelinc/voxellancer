#pragma once

#include "vec3helper.h"

bool operator>=(const glm::vec3 &a, const glm::vec3 &b) {
    return a.x >= b.x && a.y >= b.y && a.z >= b.z;
}

bool operator<=(const glm::vec3 &a, const glm::vec3 &b) {
    return a.x <= b.x && a.y <= b.y && a.z <= b.z;
}

