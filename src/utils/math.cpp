#include "math.h"

#include <iostream>

#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "randvec.h"



float Math::angleBetween(const glm::vec3& u, const glm::vec3& v) {
    float angle = glm::acos(glm::clamp(glm::dot(glm::normalize(u), glm::normalize(v)), 0.0f, 1.0f));
    assert(std::isfinite(angle));
    return angle;
}

glm::quat Math::differenceFromViewDirection(const glm::vec3& direction) {
    glm::vec3 v = direction;
    glm::vec3 u = glm::vec3(0, 0, -1);

    float angle = glm::degrees(angleBetween(u, v));
    glm::vec3 w = glm::cross(u, v);
    if (w == glm::vec3(0)) {
        w = RandVec3::randUnitVec();
    }
    return glm::angleAxis(angle, glm::normalize(w));
}

