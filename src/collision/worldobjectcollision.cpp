#include "worldobjectcollision.h"

#include <cassert>

#include "worldobject/worldobject.h"


WorldObjectCollision::WorldObjectCollision(WorldObject* worldObjectA, WorldObject* worldObjectB):
    m_worldObjectA(worldObjectA),
    m_worldObjectB(worldObjectB)
{
    assert(m_worldObjectA);
    assert(m_worldObjectB);
}

WorldObject* WorldObjectCollision::worldObjectA() {
    return m_worldObjectA;
}

WorldObject* WorldObjectCollision::worldObjectB() {
    return m_worldObjectB;
}

std::list<VoxelCollision>& WorldObjectCollision::voxelCollisions() {
    return m_voxelCollisions;
}

void WorldObjectCollision::addVoxelCollision(VoxelCollision& voxelCollision) {
    if(voxelCollision.a().worldObject() == m_worldObjectA && voxelCollision.b().worldObject() == m_worldObjectB) {
        m_voxelCollisions.push_back(voxelCollision);
    }
    else {
        assert(voxelCollision.a().worldObject() == m_worldObjectB && voxelCollision.b().worldObject() == m_worldObjectA);
        m_voxelCollisions.push_back(VoxelCollision(voxelCollision.b(), voxelCollision.a()));
    }
}
