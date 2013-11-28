#include "voxelhangman.h"

#include "voxel/voxelcluster.h"


void VoxelHangman::applyOnDestructionHooks(std::list<VoxelImpact> &deadlyVoxelImpacts) {
    for(VoxelImpact &voxelImpact : deadlyVoxelImpacts) {
        voxelImpact.voxel()->onDestruction();
    }
}

void VoxelHangman::removeDestroyedVoxels(std::list<VoxelImpact> &deadlyVoxelImpacts) {
    for(VoxelImpact &voxelImpact : deadlyVoxelImpacts) {
        Voxel *voxel = voxelImpact.voxel();
        voxel->voxelCluster()->removeVoxel(voxel->gridCell());
    }
}

