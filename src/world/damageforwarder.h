#pragma once

#include <list>

#include "voxelimpact.h"


class DamageForwarder
{
public:
    void forwardDamage(std::list<VoxelImpact> &dampedDeadlyVoxelImpacts);
    std::list<VoxelImpact> &forwardedDamageImpacts();


protected:
    std::list<VoxelImpact> m_forwardedDamageImpacts;

    VoxelCluster *m_currentVoxelCluster;
    std::list<Voxel*> *m_currentNeighbours;
    glm::ivec3 m_currentGridCell;

    std::list<Voxel*> getNeighbours(Voxel *voxel);
    void considerNeighbour(const glm::ivec3 &cellDelta);
};

