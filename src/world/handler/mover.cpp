#include "mover.h"

#include ""world/god.h"
#include "world/world.h"
#include "world/worldobject.h"


void Mover::moveVoxelClusters(float deltaSec) {
    m_collisions.clear();

    for (WorldObject *worldObject : World::instance()->worldObjects()) {
        std::list<Collision> &collisions = worldObject->move(deltaSec);
        m_collisions.insert(m_collisions.end(), collisions.begin(), collisions.end());
    }
}

const std::list<Collision> &Mover::collisions() {
    return m_collisions;
}
