#pragma once

#include <list>

#include "collision/collision.h"

#include "impact.h"

class PhysicalVoxelImpact;

class ImpactAccumulator
{
public:
    void clear();

    void parse(const std::list<Collision> &collisions);
//    void parse(const std::list<Impact> &impacts);

//    std::list<VoxelClusterImpact> &clusterImpacts();
    std::list<Impact> &impacts();


protected:
//    std::list<VoxelClusterImpact> m_clusterImpacts;
    std::list<Impact> m_impacts;
};

