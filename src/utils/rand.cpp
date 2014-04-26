#include "randvec3.h"
#include "randfloat.h"
#include "randbool.h"

#include <cassert>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>


bool RandBool::rand(float trueProbability) {
    assert(trueProbability >= 0.0f && trueProbability <= 1.0f);
    return RandFloat::rand(0.0f, 1.0f) < trueProbability;
}

float RandFloat::rand(float from, float to) {
    assert(from <= to);
    return from + (float)std::rand() / (float)(RAND_MAX / (to - from));
}

float RandFloat::randomize(float value, float randomization) {
    assert(randomization >= 0.0f && randomization <= 1.0f);
    return value * RandFloat::rand(1.0f - randomization, 1.0f + randomization);
}

glm::vec3 RandVec3::rand(float from, float to) {
    return glm::vec3(
        RandFloat::rand(from, to),
        RandFloat::rand(from, to),
        RandFloat::rand(from, to)
    );
}

glm::vec3 RandVec3::rand(const glm::vec3& from, const glm::vec3& to) {
    float x = RandFloat::rand(from.x, to.x);
    float y = RandFloat::rand(from.y, to.y);
    float z = RandFloat::rand(from.z, to.z);

    return glm::vec3(x, y, z);
}

glm::vec3 RandVec3::randUnitVec() {
    float angX = RandFloat::rand(-glm::pi<float>(), glm::pi<float>());
    float angY = glm::acos(RandFloat::rand(-1.0f, 1.0f));
    glm::vec3 result = glm::quat(glm::vec3(angX, angY, 0.0f)) * glm::vec3(0.0f, 0.0f, 1.0f);
    return glm::normalize(result);
}

