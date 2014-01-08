#include "randvec.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "randfloat.h"


glm::vec3 RandVec3::rand(float from, float to) {
    return glm::vec3(
        RandFloat::rand(from, to),
        RandFloat::rand(from, to),
        RandFloat::rand(from, to)
    );
}

glm::vec3 RandVec3::randNormalized() {
    float angX = RandFloat::rand(-180.0f, 180.0f);
    float angY = glm::degrees(glm::acos(RandFloat::rand(-1.0f, 1.0f)));
    glm::vec3 result = glm::quat(glm::vec3(angX, angY, 0.0f)) * glm::vec3(0.0f, 0.0f, 1.0f);
    return glm::normalize(result);
}
