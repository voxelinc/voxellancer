#pragma once

#include "collision/collision.h"

#include "god.h"


class Mover
{
public:
    Mover(God &god);

    void moveVoxelClusters();

    const std::list<Collision*> &collisions();
};

