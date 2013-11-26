#pragma once

#include <list>

#include "world/voxelimpact.h"

class PhysicalVoxelCluster;

class Damager
{
public:
    void applyDamages(std::list<VoxelImpact> &voxelImpacts);

    std::list<VoxelImpact> &deadlyVoxelImpacts();
    std::list<PhysicalVoxelCluster*> &modifiedVoxelClusters();

protected:
    std::list<VoxelImpact> m_deadlyVoxelImpacts;
    std::list<PhysicalVoxelCluster*> m_modifiedVoxelClusters;
};

