#pragma once

#include "collision/collision.h"

#include "god.h"


class Mover
{
public:
    void moveVoxelClusters();

    const std::list<Collision> &collisions();


protected:
    std::list<Collision> m_collisions;
};

