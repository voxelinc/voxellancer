#include "math.h"

#include <iostream>

#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>


glm::quat Math::differenceFromViewDirection(const glm::vec3& dir) {
    return xyDifference(glm::vec3(0, 0, -1), dir);
}

glm::quat Math::xyDifference(const glm::vec3& from, const glm::vec3& to) {
    glm::vec3 rotationAxis = glm::cross(from, to)
}

