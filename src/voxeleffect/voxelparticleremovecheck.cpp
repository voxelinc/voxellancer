#include "voxelparticleremovecheck.h"

#include <cassert>

#include "voxelparticledata.h"
#include "voxelparticleengine.h"


VoxelParticleRemoveCheck::VoxelParticleRemoveCheck(VoxelParticleEngine* world):
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

    int checkCount = static_cast<int>((deltaSec * m_world->particleDataCount()) / m_interval);
    checkCount = std::min(checkCount, m_world->particleDataCount());

    if (isParallel(checkCount)) {
        performChecksParallel(checkCount);
    } else {
        performChecksSequential(checkCount);
    }

    m_currentIndex = (m_currentIndex + checkCount) % m_world->particleDataCount();
}

void VoxelParticleRemoveCheck::performChecksParallel(int checkCount) {
    int firstIndex = m_currentIndex;

    std::vector<bool> deadParticles(checkCount, false);

#pragma omp parallel for
    for (int i = 0; i < checkCount; i++) {
        int bufferIndex = (firstIndex + i) % m_world->particleDataCount();
        VoxelParticleData* particle = m_world->particleData(bufferIndex);

        if(!particle->dead) { // Needed, otherwise dead Particles might be free'd twice
            deadParticles[i] = check(particle);
        }
    }

    for(int i = 0; i < checkCount; i++) {
        if(deadParticles[i]) {
            int bufferIndex = (firstIndex + i) % m_world->particleDataCount();
            m_world->removeParticle(bufferIndex);
        }
    }
}

void VoxelParticleRemoveCheck::performChecksSequential(int checkCount) {
    int firstIndex = m_currentIndex;

    for (int i = 0; i < checkCount; i++) {
        int bufferIndex = (firstIndex + i) % m_world->particleDataCount();
        VoxelParticleData* particle = m_world->particleData(bufferIndex);

        if(!particle->dead && check(particle)) { // Needed, otherwise dead Particles might be free'd twice
            m_world->removeParticle(bufferIndex);
        }
    }

}

