#include "mover.h"

#include "world/god.h"
#include "world/world.h"
#include "world/worldobject.h"


void Mover::moveVoxelClusters(float deltaSec) {
    m_impacts.clear();

    for (WorldObject *worldObject : World::instance()->worldObjects()) {
        std::list<Impact> &collisions = worldObject->move(deltaSec);
        m_impacts.insert(m_impacts.end(), collisions.begin(), collisions.end());
    }
}

const std::list<Impact> &Mover::impacts() {
    return m_impacts;
}
