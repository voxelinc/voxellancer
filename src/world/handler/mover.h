#pragma once

#include <list>
#include "collision/collision.h"

class Mover
{
public:
    void moveVoxelClusters(float deltaSec);

    const std::list<Collision> &collisions();


protected:
    std::list<Collision> m_collisions;
};

