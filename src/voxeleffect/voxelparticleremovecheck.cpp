#include "voxelparticleremovecheck.h"

#include <cassert>

#include "voxelparticledata.h"
#include "voxelparticleworld.h"


VoxelParticleRemoveCheck::VoxelParticleRemoveCheck(VoxelParticleWorld* world):
    m_world(world),
    m_currentIndex(0),
    m_interval(1.0f)
{

}

float VoxelParticleRemoveCheck::interval() const {
    return m_interval;
}

void VoxelParticleRemoveCheck::setInterval(float interval) {
    assert(interval > 0.0f);
    m_interval = interval;
}

void VoxelParticleRemoveCheck::update(float deltaSec) {
    assert(m_interval > 0.0f);

    // In case the datacount decreased
    m_currentIndex = std::min(m_currentIndex, m_world->particleDataCount());

    int checkCount = (deltaSec * m_world->particleDataCount()) / m_interval;
    checkCount = std::min(checkCount, m_world->particleDataCount());

    if(checkCount == 0) {
        return;
    }

    int lastParticle = ((m_currentIndex + checkCount - 1) % m_world->particleDataCount());

    while(true) {
        VoxelParticleData* particle = m_world->particleData(m_currentIndex);

        if (check(particle)) {
            m_world->removeParticle(m_currentIndex);
        }

        if (m_currentIndex == lastParticle) {
            break;
        }

        m_currentIndex = (m_currentIndex + 1) % m_world->particleDataCount();
    }
}
