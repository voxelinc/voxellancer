#include "mover.h"

#include "physics/physics.h"

#include "universe/sector.h"

#include "worldobject/worldobject.h"


Mover::Mover(Sector& sector):
    m_sector(sector)
{
}

void Mover::moveWorldObjects(float deltaSec) {
    m_voxelCollisions.clear();

    m_sector.foreachWorldObject( [&] (glow::ref_ptr<WorldObject>& object) {
        std::list<VoxelCollision> &collisions = object->physics().move(deltaSec);
        m_voxelCollisions.splice(m_voxelCollisions.end(), collisions);
    });
}

std::list<VoxelCollision>& Mover::voxelCollisions() {
    return m_voxelCollisions;
}

