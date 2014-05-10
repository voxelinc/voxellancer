#include "voxelexplosion.h"


VoxelExplosion::VoxelExplosion(Voxel& voxel):
    m_voxel(voxel)
{
}

VoxelExplosion::~VoxelExplosion() = default;

Voxel& VoxelExplosion::voxel() {
    return m_voxel;
}

void VoxelExplosion::spawn() {
    onSpawn();
}

