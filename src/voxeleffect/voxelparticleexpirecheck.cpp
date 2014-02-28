#include "voxelparticleexpirecheck.h"

#include "voxelparticledata.h"

#include "voxelparticleengine.h"


VoxelParticleExpireCheck::VoxelParticleExpireCheck(VoxelParticleEngine* engine):
    VoxelParticleRemoveCheck(engine),
    m_fullDeadCheckInterval("vfx.fullDeadCheckInterval")
{
}

void VoxelParticleExpireCheck::update(float deltaSec) {
    setInterval(m_fullDeadCheckInterval);
    VoxelParticleRemoveCheck::update(deltaSec);
}

bool VoxelParticleExpireCheck::check(VoxelParticleData* particleData) {
	return particleData->deathTime <= m_engine->time();
}

/*
    Always single threaded as these are pretty fast
*/
bool VoxelParticleExpireCheck::isParallel(int checkCount) {
    return false;
}

