#pragma once

#include <list>

#include "collision/collision.h"


class PhysicalVoxelImpact;

class ImpactAccumulator
{
public:
    void clear();

    void parse(const std::list<Collision> &collisions);
    void parse(const std::list<PhysicalVoxelImpact> &physicalVoxelImpacts);

    //std::list<VoxelClusterImpact> &clusterImpacts();
    std::list<PhysicalVoxelImpact> &physicalVoxelImpacts();


protected:
    //std::list<VoxelClusterImpact> m_clusterImpacts;
    std::list<PhysicalVoxelImpact> m_physicalVoxelImpacts;
};

