#pragma once

#include "collision/collision.h"


class ImpactAccumulator
{
public:
    ImpactAccumulator();

    void parse(const std::list<Collision*> &collisions);
    void parse(const std::list<VoxelImpact*> &voxelImpacts);

    std::list<VoxelClusterImpact*> &voxelClusterImpacts();

};

