#include "voxelhangman.h"


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

