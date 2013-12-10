#include "voxelhangman.h"

#include <cassert>

#include "voxel/voxel.h"
#include "worldobject/worldobject.h"


void VoxelHangman::applyOnDestructionHooks(std::list<Impact> &deadlyImpacts) {
    for(Impact &impact : deadlyImpacts) {
        assert(impact.voxel() != nullptr);
        impact.voxel()->onDestruction();
    }
}

void VoxelHangman::removeDestroyedVoxels(std::list<Impact> &deadlyImpacts) {
    for(Impact &impact : deadlyImpacts) {
        impact.worldObject()->removeVoxel(impact.voxel()->gridCell());
    }
}


