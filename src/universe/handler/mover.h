#pragma once

#include <list>

#include <glow/ref_ptr.h>

#include "collision/voxelcollision.h"
#include "physics/impulse.h"


class WorldObject;

class Mover {
public:
    void moveWorldObjects(const std::list<glow::ref_ptr<WorldObject>>& objects, float deltaSec);

    std::list<VoxelCollision>& voxelCollisions();


protected:
    std::list<VoxelCollision> m_voxelCollisions;
};

