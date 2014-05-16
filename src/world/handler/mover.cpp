#include "mover.h"

#include "physics/physics.h"

#include "worldobject/worldobject.h"


void Mover::moveWorldObjects(const std::list<WorldObject*>& objects, float deltaSec) {
    m_voxelCollisions.clear();

    for (WorldObject* object : objects) {
        std::list<VoxelCollision> &collisions = object->physics().move(deltaSec);
        m_voxelCollisions.splice(m_voxelCollisions.end(), collisions);
    }
}

std::list<VoxelCollision> &Mover::voxelCollisions() {
    return m_voxelCollisions;
}

