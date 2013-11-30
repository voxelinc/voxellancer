#pragma once

#include <list>

#include "voxelimpact.h"


class VoxelHangman
{
public:
    void applyOnDestructionHooks(std::list<VoxelImpact> &deadlyVoxelImpacts);
    void removeDestroyedVoxels(std::list<VoxelImpact> &deadlyVoxelImpacts);
};

