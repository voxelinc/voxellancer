#include "randfloatpool.h"

#include <cassert>
#include <iostream>

#include "randfloat.h"


const static int POOL_SIZE = 1024;

std::vector<float> RandFloatPool::s_pool;
int RandFloatPool::s_iter(0);


float RandFloatPool::rand(float from, float to) {
    float randBase = s_pool[s_iter & 0x3FF];
    s_iter++;

    return from + (to - from) * randBase;
}

float RandFloatPool::randomize(float value, float randomization) {
    assert(randomization >= 0.0f && randomization <= 1.0f);
    return value * rand(1.0f - randomization, 1.0f + randomization);
}

void RandFloatPool::initialize() {
    assert(s_pool.size() == 0);
    s_pool.resize(POOL_SIZE);
    for (int i = 0; i < POOL_SIZE; i++) {
        s_pool[i] = RandFloat::rand(0.0f, 1.0f);
    }
}

RandFloatPool::_Init::_Init() {
    initialize();
};
namespace {
    RandFloatPool::_Init _init;
}
