#include "voxelparticleengine.h"

#include "voxelparticleengineimpl.h"
#include "voxelparticlesetup.h"


VoxelParticleEngine::VoxelParticleEngine():
    m_opaqueEngine(new VoxelParticleEngineImpl()),
    m_transparentEngine(new VoxelParticleEngineImpl())
{
}

VoxelParticleEngine::~VoxelParticleEngine() = default;

int VoxelParticleEngine::particleCount() const {
    return m_opaqueEngine->particleCount() + m_transparentEngine->particleCount();
}

void VoxelParticleEngine::setPlayer(Player& m_player) {
    m_opaqueEngine->setPlayer(m_player);
    m_transparentEngine->setPlayer(m_player);
}

void VoxelParticleEngine::addParticle(const VoxelParticleSetup& particleSetup, const VoxelCluster* creator) {
    if ((particleSetup.visuals().color() & 0xFF) == 0xFF) {
        m_opaqueEngine->addParticle(particleSetup, creator);
    } else {
        m_transparentEngine->addParticle(particleSetup, creator);
    }
}

void VoxelParticleEngine::update(float deltaSec) {
    m_opaqueEngine->update(deltaSec);
    m_transparentEngine->update(deltaSec);
}

void VoxelParticleEngine::draw(const Camera& camera, bool transparentPass) {
    if (transparentPass) {
        m_transparentEngine->draw(camera, true);
    } else {
        m_opaqueEngine->draw(camera, false);
    }
}