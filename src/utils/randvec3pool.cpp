#include "randvec3pool.h"

#include "randvec3.h"


const static int POOL_SIZE = 1024;

std::vector<glm::vec3> RandVec3Pool::s_pool;
int RandVec3Pool::s_iter(0);

glm::vec3 RandVec3Pool::randUnitVec() {
    if (s_pool.empty()) {
        initialize();
    }

    glm::vec3 result = s_pool[s_iter];
    s_iter = (s_iter + 1) % s_pool.size();

    return result;
}

void RandVec3Pool::initialize() {
    s_pool.resize(POOL_SIZE);
    for (int i = 0; i < POOL_SIZE; i++) {
        s_pool[i] = RandVec3::randUnitVec();
    }
}

