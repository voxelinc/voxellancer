#pragma once

#include <list>
#include "collision/collision.h"
#include "world/handler/impact.h"

class Mover
{
public:
    void moveVoxelClusters(float deltaSec);

    const std::list<Impact> &collisions();


protected:
    std::list<Impact> m_collisions;
};

