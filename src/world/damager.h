#pragma once

#include <set>
#include <list>


#include "voxelclusterimpact.h"


class Damager
{
public:
    void applyDamages(std::list<VoxelImpact> &voxelImpacts);

    std::list<VoxelImpact> &deadlyVoxelImpacts();
    std::set<VoxelCluster*> &modifiedVoxelClusters();


protected:
    std::list<VoxelImpact> m_deadlyVoxelImpacts;
    std::set<VoxelCluster*> m_modifiedVoxelClusters;

    float damageOfImpact(const Impact &impact) const;
};

