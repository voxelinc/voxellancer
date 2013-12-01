#pragma once

#include <list>

#include "world/helper/impact.h"


class DamageForwarder
{
public:
    void forwardDamage(std::list<Impact> &dampedDeadlyImpacts);
    std::list<Impact> &forwardedDamageImpacts();


protected:
    std::list<Impact> m_forwardedDamageImpacts;

    WorldObject *m_currentWorldObject;
    std::list<Voxel*> *m_currentNeighbours;
    glm::ivec3 m_currentGridCell;

    std::list<Voxel*> getNeighbours(Voxel *voxel);
    void considerNeighbour(const glm::ivec3 &cellDelta);
};

