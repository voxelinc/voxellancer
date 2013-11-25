#pragma once

#include <set>
#include <list>


#include "voxelclusterimpact.h"


class Damager
{
public:
    void applyDamages(std::list<VoxelImpact> &voxelImpacts);

    std::list<VoxelImpact> &dampedDeadlyVoxelImpacts();
    std::list<Voxel*> &deadVoxels();
    std::set<VoxelCluster*> &modifiedVoxelClusters();


protected:
    std::list<VoxelImpact> m_dampedDeadlyVoxelImpacts;
    std::list<Voxel*> m_deadVoxels;
    std::set<VoxelCluster*> m_modifiedVoxelClusters;

    float damageOfImpact(const Impact &impact) const;
    VoxelImpact dampVoxelImpact(VoxelImpact &undamped, float factor);
};

