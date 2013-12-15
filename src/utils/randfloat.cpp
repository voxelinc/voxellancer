#include "randfloat.h"

#include "glm/glm.hpp"

float RandFloat::rand(float from, float to){
    return from + (float)std::rand() / (float)(RAND_MAX / (to - from));
}
