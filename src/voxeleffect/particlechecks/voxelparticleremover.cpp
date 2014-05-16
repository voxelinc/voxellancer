#include "voxelparticleremover.h"

#include <cassert>

#include "utils/threadpool.h"

#include "voxeleffect/voxelparticledata.h"
#include "voxeleffect/voxelparticleengine.h"

#include "voxelparticleremovecheck.h"


VoxelParticleRemover::VoxelParticleRemover(VoxelParticleEngine* world):
    m_particleEngine(world),
    m_currentIndex(0),
    m_interval("particle.checkinterval"),
    m_multithreaded("particle.multithreaded"),
    m_threadPool(new ThreadPool<VoxelParticleData>(4))
{

}

VoxelParticleRemover::~VoxelParticleRemover() = default;

void VoxelParticleRemover::update(float deltaSec) {
    assert(m_interval > 0.0f);

    // In case the datacount decreased
    m_currentIndex = std::min(m_currentIndex, m_particleEngine->particleDataCount());

    int checkCount = static_cast<int>((deltaSec * m_particleEngine->particleDataCount()) / m_interval);
    checkCount = std::min(checkCount, m_particleEngine->particleDataCount());

    beforeCheck();
    performChecks(checkCount);

    m_currentIndex = (m_currentIndex + checkCount) % m_particleEngine->particleDataCount();
}

void VoxelParticleRemover::performChecks(int checkCount) {
    int firstIndex = m_currentIndex;

    // glow::debug("check %; %;", firstIndex, checkCount);
    if (m_multithreaded.get()) {
        m_threadPool->map([&](VoxelParticleData& p) { isDead(p); }, m_particleEngine->particleDataVector(), firstIndex, firstIndex + checkCount);

        for (int i = firstIndex; i < firstIndex + checkCount; i++) {
            int index = i % m_particleEngine->particleDataCount();
            if (m_particleEngine->particleData(index)->status == VoxelParticleData::Status::Dead) {
                m_particleEngine->removeParticle(index);
            }
        }
    } else {
        for (int i = firstIndex; i < firstIndex + checkCount; i++) {
            int index = i % m_particleEngine->particleDataCount();
            VoxelParticleData* particle = m_particleEngine->particleData(index);
            if (isDead(*particle)) {
                m_particleEngine->removeParticle(index);
            }
        }

    }
}

bool VoxelParticleRemover::isDead(VoxelParticleData& particle) {
    if (particle.status != VoxelParticleData::Status::Alive) {
        return false;
    }

    for (std::shared_ptr<VoxelParticleRemoveCheck>& checker : m_checker) {
        if (checker->isDead(particle)) {
            particle.status = VoxelParticleData::Status::Dead;
            return true;
        }
    }

    return false;
}

void VoxelParticleRemover::addCheck(std::shared_ptr<VoxelParticleRemoveCheck> checker) {
    m_checker.push_back(checker);
}

void VoxelParticleRemover::setPlayer(Player& player) {
    for (std::shared_ptr<VoxelParticleRemoveCheck>& checker : m_checker) {
        checker->setPlayer(player);
    }
}

void VoxelParticleRemover::beforeCheck() {
    for (std::shared_ptr<VoxelParticleRemoveCheck>& checker : m_checker) {
        checker->beforeCheck();
    }
}

