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

uint32_t RandFloat::_xor_rand() {
    static uint32_t r = 2463534242UL;
    r ^= (r << 13);
    r ^= (r >> 17);
    r ^= (r << 5);
    return r;
}

float RandFloat::rand_xor(float from, float to) {
    return from + static_cast<float>(_xor_rand()) / 4294967296.f * (to - from); // divide by 2^32
}

glm::vec3 RandVec3::rand(float from, float to) {
    return glm::vec3(
        RandFloat::rand(from, to),
        RandFloat::rand(from, to),
        RandFloat::rand(from, to)
    );
}

glm::vec3 RandVec3::randUnitVec() {
    float angX = RandFloat::rand(-glm::pi<float>(), glm::pi<float>());
    float angY = glm::acos(RandFloat::rand(-1.0f, 1.0f));
    glm::vec3 result = glm::quat(glm::vec3(angX, angY, 0.0f)) * glm::vec3(0.0f, 0.0f, 1.0f);
    return glm::normalize(result);
}

