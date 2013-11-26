#pragma once

#include <list>

#include "voxelimpact.h"


class VoxelHangman
{
public:
    void applyOnDestructionHooks(std::list<Voxel*> &deadVoxels);
    void removeDestroyedVoxels(std::list<Voxel*> &deadVoxels);
};

