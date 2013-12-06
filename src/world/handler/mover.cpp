#include "mover.h"

#include "world/god.h"
#include "world/world.h"
#include "worldobject/worldobject.h"


void Mover::moveWorldObjects(float deltaSec) {
    m_collisions.clear();

    for (WorldObject *worldObject : World::instance()->worldObjects()) {
        std::list<Collision> &collisions = worldObject->move(deltaSec);
        m_collisions.splice(m_collisions.end(), collisions);
    }
}

const std::list<Collision> &Mover::collisions() {
    return m_collisions;
}

