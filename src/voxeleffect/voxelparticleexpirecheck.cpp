#include "voxelparticleexpirecheck.h"

#include "voxelparticledata.h"

#include "voxelparticleengine.h"


VoxelParticleExpireCheck::VoxelParticleExpireCheck(const VoxelParticleEngine& engine):
    m_particleEngine(engine)
{
}


bool VoxelParticleExpireCheck::isDead(const VoxelParticleData& particleData) {
	return particleData.deathTime <= m_particleEngine.time();
}

