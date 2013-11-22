#pragma once

#include <list>

#include "collision/collision.h"

#include "voxelclusterimpact.h"


class ImpactAccumulator
{
public:
    void clear();

    void parse(const std::list<Collision> &collisions);
    void parse(const std::list<VoxelImpact> &voxelImpacts);

    std::list<VoxelClusterImpact> &clusterImpacts();
    std::list<VoxelImpact> &voxelImpacts();


protected:
    std::list<VoxelClusterImpact> m_clusterImpacts;
    std::list<VoxelImpact> m_voxelImpacts;
};

