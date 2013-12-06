#pragma once

#include <list>
#include "collision/collision.h"
#include "world/helper/impact.h"

class Mover
{
public:
    void moveWorldObjects(float deltaSec);

    const std::list<Collision>& collisions();


protected:
    std::list<Collision> m_collisions;
};

