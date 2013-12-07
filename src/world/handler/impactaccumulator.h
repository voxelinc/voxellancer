#pragma once

#include <list>
#include <map>

#include "collision/collision.h"

#include "world/helper/impact.h"


class Voxel;

class ImpactAccumulator
{
public:
    void clear();

    void parse(const std::list<Collision> &collisions);
    void parse(const std::list<Impact> &impacts);

    void dontImpact(const std::list<Voxel*> voxels);

    std::list<Impact>& impacts();


protected:
    std::map<const Voxel*, Impact> m_voxelImpactMap;
    std::map<WorldObject*, std::list<Collision>> m_worldObjectCollisions;

    std::list<Impact> m_impacts;

    void parseCollision(WorldObject *worldObject, const Collision& collision);
};

