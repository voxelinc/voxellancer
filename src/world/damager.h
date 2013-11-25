#pragma once

#include <list>

#include "voxelclusterimpact.h"


class Damager
{
public:
    void applyDamages(std::list<VoxelImpact> &voxelImpacts);

    std::list<VoxelImpact> &deadlyVoxelImpacts();
    std::list<VoxelCluster*> &modifiedVoxelClusters();

protected:
    std::list<VoxelImpact> m_deadlyVoxelImpacts;
    std::list<VoxelCluster*> m_modifiedVoxelClusters;
};

