#pragma once

#include <list>

#include "universe/helper/damageimpact.h"


class VoxelHangman {
public:
    void applyOnDestructionHooks(std::list<DamageImpact> &deadlyDamageImpacts);
    void removeDestroyedVoxels(std::list<DamageImpact> &deadlyDamageImpacts);
};

