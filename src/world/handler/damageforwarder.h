#pragma once

#include <list>

#include "impact.h"


class DamageForwarder
{
public:
    void forwardDamage(std::list<Impact> &dampedDeadlyImpacts);
    std::list<VoxelImpact> &forwardedDamageImpacts();


protected:
    std::list<VoxelImpact> m_forwardedDamageImpacts;

    WorldObject *m_currentWorldObject;
    std::list<Voxel*> *m_currentNeighbours;
    glm::ivec3 m_currentGridCell;

    std::list<Voxel*> getNeighbours(WorldObject *voxel);
    void considerNeighbour(const glm::ivec3 &cellDelta);
};

