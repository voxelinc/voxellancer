#pragma once

#include <list>
#include "collision/voxelcollision.h"
#include "world/helper/impact.h"

class Mover
{
public:
    void moveWorldObjects(float deltaSec);

    std::list<VoxelCollision>& voxelCollisions();


protected:
    std::list<VoxelCollision> m_voxelCollisions;
};

