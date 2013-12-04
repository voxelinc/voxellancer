#include "mover.h"

#include "world/god.h"
#include "world/world.h"
#include "worldobject/worldobject.h"


void Mover::moveWorldObjects(float deltaSec) {
    m_impacts.clear();

    for (WorldObject *worldObject : World::instance()->worldObjects()) {
        std::list<Impact> &impacts = worldObject->move(deltaSec);
        m_impacts.insert(m_impacts.end(), impacts.begin(), impacts.end());
    }
}

const std::list<Impact> &Mover::impacts() {
    return m_impacts;
}

