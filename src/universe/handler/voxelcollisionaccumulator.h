#pragma once

#include <list>

#include "collision/worldobjectcollision.h"


class VoxelCollision;

class VoxelCollisionAccumulator {
public:
    void parse(std::list<VoxelCollision>& voxelCollisions);
    void applyOnCollsionHooks();

    std::list<WorldObjectCollision>& worldObjectCollisions();
    std::list<WorldObject*>& worldObjects();


protected:
    std::list<WorldObjectCollision> m_worldObjectCollisions;
    std::list<WorldObject*> m_worldObjects;
};

