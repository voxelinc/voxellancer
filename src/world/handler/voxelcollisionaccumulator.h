#pragma once

#include <list>

#include "collision/worldobjectcollision.h"


class VoxelCollision;

class VoxelCollisionAccumulator {
public:
    void parse(std::list<VoxelCollision>& voxelCollisions);

    std::list<WorldObjectCollision>& worldObjectCollisions();


protected:
    std::list<WorldObjectCollision> m_worldObjectCollisions;
};

