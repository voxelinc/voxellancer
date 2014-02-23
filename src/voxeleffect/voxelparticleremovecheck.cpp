#include "voxelparticleremovecheck.h"

#include <cassert>

#include "voxelparticledata.h"
#include "voxelparticleengine.h"
#include "voxelparticlechecker.h"


VoxelParticleRemoveCheck::VoxelParticleRemoveCheck(VoxelParticleEngine* world):
    m_particleEngine(world),
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
    m_currentIndex = std::min(m_currentIndex, m_particleEngine->particleDataCount());

    int checkCount = static_cast<int>((deltaSec * m_particleEngine->particleDataCount()) / m_interval);
    checkCount = std::min(checkCount, m_particleEngine->particleDataCount());

    performChecks(checkCount);
    
    m_currentIndex = (m_currentIndex + checkCount) % m_particleEngine->particleDataCount();
}


void VoxelParticleRemoveCheck::performChecks(int checkCount) {
    int firstIndex = m_currentIndex;

    for (int i = firstIndex; i < firstIndex + checkCount; i++) {
        VoxelParticleData* particle = m_particleEngine->particleData(i % m_particleEngine->particleDataCount());
        check(*particle);
    }

    for (int i = firstIndex; i < firstIndex + checkCount; i++) {
        if (m_particleEngine->particleData(i % m_particleEngine->particleDataCount())->status == VoxelParticleData::Status::Dead) {
            m_particleEngine->removeParticle(i % m_particleEngine->particleDataCount());
        }
    }
}

void VoxelParticleRemoveCheck::check(VoxelParticleData& particle) {
    if (particle.status != VoxelParticleData::Status::Alive) {
        return;
    }

    for (std::shared_ptr<VoxelParticleChecker>& checker : m_checker) {
        if (checker->isDead(particle)) {
            particle.status = VoxelParticleData::Status::Dead;
            return;
        }
    }
}

void VoxelParticleRemoveCheck::addCheck(std::shared_ptr<VoxelParticleChecker> checker) {
    m_checker.push_back(checker);
}
