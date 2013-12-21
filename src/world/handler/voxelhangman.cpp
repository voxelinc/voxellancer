#include "voxelhangman.h"

#include <cassert>

#include "voxel/voxel.h"
#include "worldobject/worldobject.h"


void VoxelHangman::applyOnDestructionHooks(std::list<DamageImpact> &deadlyDamageImpacts) {
    for(DamageImpact& damageImpact : deadlyDamageImpacts) {
        assert(damageImpact.voxel() != nullptr);
        damageImpact.voxel()->onDestruction();
    }
}

void VoxelHangman::removeDestroyedVoxels(std::list<DamageImpact> &deadlyDamageImpacts) {
    for(DamageImpact& damageImpact : deadlyDamageImpacts) {
        damageImpact.worldObject()->removeVoxel(damageImpact.voxel());
    }
}


