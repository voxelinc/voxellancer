#include "randfloat.h"

#include <cassert>

#include "glm/glm.hpp"


float RandFloat::rand(float from, float to) {
    assert(from <= to);
    return from + (float)std::rand() / (float)(RAND_MAX / (to - from));
}

float RandFloat::randomize(float value, float randomization) {
    assert(randomization >= 0.0f && randomization <= 1.0f);
    return value * RandFloat::rand(1.0f - randomization, 1.0f + randomization);
}

