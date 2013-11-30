#include "voxelhangman.h"

#include "voxel/voxel.h"
#include "world/worldobject.h"


void VoxelHangman::applyOnDestructionHooks(std::list<Impact> &deadlyImpacts) {
    for(Impact &impact : deadlyImpacts) {
        impact.voxel()->onDestruction();
    }
}

void VoxelHangman::removeDestroyedVoxels(std::list<Impact> &deadlyImpacts) {
    for(Impact &impact : deadlyImpacts) {
        impact.worldObject()->removeVoxel(impact.voxel()->gridCell());
    }
}

