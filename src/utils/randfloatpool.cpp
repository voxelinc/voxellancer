#include "randfloatpool.h"

#include <cassert>
#include <iostream>

#include "randfloat.h"


const static int POOL_SIZE = 1024;

std::weak_ptr<RandFloatPool> RandFloatPool::s_instance;

std::shared_ptr<RandFloatPool> RandFloatPool::instance() {
    if (std::shared_ptr<RandFloatPool> pool = s_instance.lock()) {
        return pool;
    } else {
        pool = std::shared_ptr<RandFloatPool>(new RandFloatPool());
        s_instance = pool;
        return pool;
    }
}

float RandFloatPool::rand(float from, float to) {
    assert(from <= to);

    float randBase = m_pool[m_iter];
    m_iter = (m_iter + 1) % m_pool.size();

    return from + (to - from) * randBase;
}

float RandFloatPool::randomize(float value, float randomization) {
    assert(randomization >= 0.0f && randomization <= 1.0f);
    return value * rand(1.0f - randomization, 1.0f + randomization);
}

RandFloatPool::RandFloatPool():
    m_pool(POOL_SIZE),
    m_iter(0)
{
    for (int i = 0; i < POOL_SIZE; i++) {
        m_pool[i] = RandFloat::rand(0.0f, 1.0f);
    }
}
