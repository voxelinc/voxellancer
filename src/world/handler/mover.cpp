#include "mover.h"

#include "world/god.h"
#include "world/world.h"
#include "worldobject/worldobject.h"


void Mover::moveWorldObjects(float deltaSec) {
    m_voxelCollisions.clear();

    for (WorldObject *worldObject : World::instance()->worldObjects()) {
        std::list<VoxelCollision> &collisions = worldObject->physics().move(deltaSec);
        m_voxelCollisions.splice(m_voxelCollisions.end(), collisions);
    }
}

std::list<VoxelCollision> &Mover::voxelCollisions() {
    return m_voxelCollisions;
}

