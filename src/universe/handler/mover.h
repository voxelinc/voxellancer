#pragma once

#include <list>

#include <glow/ref_ptr.h>

#include "collision/voxelcollision.h"
#include "physics/impulse.h"


class Sector;
class WorldObject;

class Mover final {
public:
    Mover(Sector& sector);

    void moveWorldObjects(float deltaSec);

    std::list<VoxelCollision>& voxelCollisions();


protected:
    Sector& m_sector;
    std::list<VoxelCollision> m_voxelCollisions;
};

