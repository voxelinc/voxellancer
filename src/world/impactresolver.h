#pragma once

#include <list>

#include "voxelclusterimpact.h"


class ImpactResolver
{
public:
    void alterVelocities(std::list<VoxelClusterImpact*> &voxelClusterImpacts);
};

