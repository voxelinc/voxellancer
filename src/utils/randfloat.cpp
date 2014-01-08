#include "randfloat.h"

#include "glm/glm.hpp"

float RandFloat::rand(float from, float to){
    return from + (float)std::rand() / (float)(RAND_MAX / (to - from));
}

float RandFloat::randomize(float value, float randomization) {
    return value * RandFloat::rand(1.0f - randomization, 1.0f + randomization);
}

