#include "voxelparticleexpirecheck.h"

#include "voxeleffect/voxelparticledata.h"
#include "voxeleffect/voxelparticleengineimpl.h"


VoxelParticleExpireCheck::VoxelParticleExpireCheck(const VoxelParticleEngineImpl& engine):
    m_particleEngine(engine)
{
}


bool VoxelParticleExpireCheck::isDead(const VoxelParticleData& particleData) {
	return particleData.deathTime <= m_particleEngine.time();
}

