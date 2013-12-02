#pragma once

#include <list>

#include "world/helper/impact.h"

#include "impactaccumulator.h"


class DamageForwarder: protected ImpactAccumulator
{
public:
    void forwardDamage(std::list<Impact> &dampedDeadlyImpacts);
    void dontForwardTo(std::list<Voxel*> &deadVoxels);

    std::list<Impact> forwardedDamageImpacts();


protected:

    WorldObject *m_currentWorldObject;
    std::list<Voxel*> *m_currentNeighbours;
    glm::ivec3 m_currentGridCell;

    std::list<Voxel*> getNeighbours(Voxel *voxel);
    void considerNeighbour(const glm::ivec3 &cellDelta);
};

