#include "voxelhangman.h"

#include "voxel/voxelcluster.h"


void VoxelHangman::applyOnDestructionHooks(std::list<Voxel*> &deadVoxels) {
    for(Voxel *voxel : deadVoxels) {
        voxel->onDestruction();
    }
}

void VoxelHangman::removeDestroyedVoxels(std::list<Voxel*> &deadVoxels) {
    for(Voxel *voxel : deadVoxels) {
        voxel->voxelCluster()->removeVoxel(voxel->gridCell());
    }
}

