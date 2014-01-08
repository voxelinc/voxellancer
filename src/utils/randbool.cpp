#include "randbool.h"

#include <cassert>

#include <glm/glm.hpp>

#include "randfloat.h"


bool RandBool::rand(float trueProbability) {
    assert(trueProbability >= 0.0f && trueProbability <= 1.0f);
    return RandFloat::rand(0.0f, 1.0f) < trueProbability;
}

