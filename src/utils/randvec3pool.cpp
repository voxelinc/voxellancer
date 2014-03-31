#include "randvec3pool.h"

#include "randvec3.h"

/**
 *  this needs to be a power of 2!
 */
const static int POOL_SIZE = 1024;

std::vector<glm::vec3> RandVec3Pool::s_pool;
int RandVec3Pool::s_iter(0);

glm::vec3 RandVec3Pool::randUnitVec() {
    glm::vec3 result = s_pool[s_iter & (POOL_SIZE - 1)];
    s_iter++;

    return result;
}

void RandVec3Pool::initialize() {
    assert(s_pool.size() == 0);
    s_pool.resize(POOL_SIZE);
    for (int i = 0; i < POOL_SIZE; i++) {
        s_pool[i] = RandVec3::randUnitVec();
    }
}

RandVec3Pool::_Init::_Init() {
    initialize();
};

namespace {
    RandVec3Pool::_Init _init;
}
