#include "voxelparticleremovecheck.h"

#include <cassert>

#include "utils/threadpool.h"

#include "voxelparticledata.h"
#include "voxelparticleengine.h"
#include "voxelparticlechecker.h"


VoxelParticleRemoveCheck::VoxelParticleRemoveCheck(VoxelParticleEngine* world):
    m_particleEngine(world),
    m_currentIndex(0),
    m_interval("particle.checkinterval"),
    m_multithreaded("particle.multithreaded"),
    m_threadPool(new ThreadPool<VoxelParticleData>(4))
{

}

VoxelParticleRemoveCheck::~VoxelParticleRemoveCheck() = default;


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

    // glow::debug("check %; %;", firstIndex, checkCount);
    if (m_multithreaded.get()) {
        m_threadPool->map([&](VoxelParticleData& p) { check(p); }, m_particleEngine->particleDataVector(), firstIndex, firstIndex + checkCount);
    } else {
        for (int i = firstIndex; i < firstIndex + checkCount; i++) {
            int index = i % m_particleEngine->particleDataCount();
            VoxelParticleData* particle = m_particleEngine->particleData(index);
            check(*particle);
        }
    }

    for (int i = firstIndex; i < firstIndex + checkCount; i++) {
        int index = i % m_particleEngine->particleDataCount();
        if (m_particleEngine->particleData(index)->status == VoxelParticleData::Status::Dead) {
            m_particleEngine->removeParticle(index);
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

