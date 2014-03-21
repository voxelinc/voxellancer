#include "randvec3pool.h"

#include "randvec3.h"


const static int POOL_SIZE = 1024;

std::weak_ptr<RandVec3Pool> RandVec3Pool::s_instance;

std::shared_ptr<RandVec3Pool> RandVec3Pool::instance() {
    if (std::shared_ptr<RandVec3Pool> pool = s_instance.lock()) {
        return pool;
    } else {
        pool = std::shared_ptr<RandVec3Pool>(new RandVec3Pool());
        s_instance = pool;
        return pool;
    }
}

glm::vec3 RandVec3Pool::randUnitVec() {
    glm::vec3 result = m_pool[m_iter];
    m_iter = (m_iter + 1) % m_pool.size();

    return result;
}

RandVec3Pool::RandVec3Pool():
    m_pool(POOL_SIZE),
    m_iter(0)
{
    for (int i = 0; i < POOL_SIZE; i++) {
        m_pool[i] = RandVec3::randUnitVec();
    }
}

