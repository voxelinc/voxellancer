#include "voxelparticleremovecheck.h"

#include <cassert>

#include "worldtree/worldtreenode.h"

#include "voxelparticledata.h"
#include "voxelparticleengine.h"


VoxelParticleRemoveCheck::VoxelParticleRemoveCheck(VoxelParticleEngine* engine):
    m_engine(engine),
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
    m_currentIndex = std::min(m_currentIndex, m_engine->particleDataCount());

    int checkCount = static_cast<int>((deltaSec * m_engine->particleDataCount()) / m_interval);
    checkCount = std::min(checkCount, m_engine->particleDataCount());

    if (isParallel(checkCount)) {
        performChecksParallel(checkCount);
    } else {
        performChecksSequential(checkCount);
    }

    m_currentIndex = (m_currentIndex + checkCount) % m_engine->particleDataCount();
}

void VoxelParticleRemoveCheck::performChecksParallel(int checkCount) {
    int firstIndex = m_currentIndex;

    std::vector<bool> deadParticles(checkCount, false);

#pragma omp parallel for
    for (int i = 0; i < checkCount; i++) {
        int bufferIndex = (firstIndex + i) % m_engine->particleDataCount();
        VoxelParticleData* particle = m_engine->particleData(bufferIndex);

        if(!particle->dead) { // Needed, otherwise dead Particles might be free'd twice
            deadParticles[i] = check(particle);
        }
    }

    for(int i = 0; i < checkCount; i++) {
        if(deadParticles[i]) {
            int bufferIndex = (firstIndex + i) % m_engine->particleDataCount();
            m_engine->removeParticle(bufferIndex);
        }
    }
}

void VoxelParticleRemoveCheck::performChecksSequential(int checkCount) {
    int firstIndex = m_currentIndex;

    for (int i = 0; i < checkCount; i++) {
        int bufferIndex = (firstIndex + i) % m_engine->particleDataCount();
        VoxelParticleData* particle = m_engine->particleData(bufferIndex);

        if(!particle->dead && check(particle)) { // Needed, otherwise dead Particles might be free'd twice
            m_engine->removeParticle(bufferIndex);
        }
    }
}

