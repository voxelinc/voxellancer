#pragma once

#include <list>

#include <glow/ref_ptr.h>

#include "voxelcollision.h"


class WorldObject;
class WorldObjectCollision;

class WorldObjectCollision {
public:
    WorldObjectCollision(WorldObject* worldObjectA, WorldObject* worldObjectB);

    WorldObject* worldObjectA();
    WorldObject* worldObjectB();

    std::list<VoxelCollision>& voxelCollisions();
    void addVoxelCollision(VoxelCollision& voxelCollision);


protected:
    glow::ref_ptr<WorldObject> m_worldObjectA;
    glow::ref_ptr<WorldObject> m_worldObjectB;
    std::list<VoxelCollision> m_voxelCollisions;
};

