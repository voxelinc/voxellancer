#pragma once

#include <list>

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
    WorldObject* m_worldObjectA;
    WorldObject* m_worldObjectB;
    std::list<VoxelCollision> m_voxelCollisions;
};
