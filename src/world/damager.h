#pragma once

#include <list>

#include "voxelclusterimpact.h"


class Damager
{
public:
    void applyDamage(std::list<VoxelClusterImpact*> &voxelClusterImpacts);

    std::list<VoxelImpact*> &deadlyVoxelImpacts();
    std::list<VoxelCluster*> &modifiedVoxelClusters();
};

