#include "voxelgraveyard.h"

#include "voxel/voxel.h"

#include "worldobject/worldobject.h"


VoxelGraveyard::VoxelGraveyard(VoxelCluster* voxelCluster):
    m_voxelCluster(voxelCluster)
{

}

VoxelGraveyard::~VoxelGraveyard() {
    for (Voxel* voxel : m_voxels) {
        delete voxel;
    }
}

void VoxelGraveyard::bury(Voxel* voxel) {
    m_voxels.push_back(voxel);
}

void VoxelGraveyard::revive(Voxel* voxel) {
    m_voxels.remove(voxel);

    WorldObject* worldObject = dynamic_cast<WorldObject*>(m_voxelCluster);
    if (worldObject) {
        voxel->addToObject(worldObject);
    } else {
        voxel->addToCluster(m_voxelCluster);
    }
}

std::list<Voxel*>& VoxelGraveyard::voxels() {
    return m_voxels;
}

