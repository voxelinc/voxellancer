#pragma once

#include <list>

#include "world/helper/impact.h"


class VoxelHangman
{
public:
    void applyOnDestructionHooks(std::list<Impact> &deadlyImpacts);
    void removeDestroyedVoxels(std::list<Impact> &deadlyImpacts);
};

