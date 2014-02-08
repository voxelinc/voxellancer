#include "voxelparticleexpirecheck.h"

#include "voxelparticledata.h"

#include "voxelparticleworld.h"


VoxelParticleExpireCheck::VoxelParticleExpireCheck(VoxelParticleWorld* world):
    VoxelParticleRemoveCheck(world),
    m_fullDeadCheckInterval("vfx.fullDeadCheckInterval")
{
}

void VoxelParticleExpireCheck::update(float deltaSec) {
    setInterval(m_fullDeadCheckInterval);
    VoxelParticleRemoveCheck::update(deltaSec);
}

bool VoxelParticleExpireCheck::check(VoxelParticleData* particleData) {
	return particleData->deathTime <= m_world->time();
}
