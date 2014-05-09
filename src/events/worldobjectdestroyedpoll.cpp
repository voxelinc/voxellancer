#include "worldobjectdestroyedpoll.h"

#include "worldobject/worldobject.h"


WorldObjectDestroyedPoll::WorldObjectDestroyedPoll(WorldObject* worldObject, const Callback& callback):
    EventPoll(callback),
    m_worldObject(makeHandle(worldObject)),
    m_fired(false)
{
}

bool WorldObjectDestroyedPoll::poll() {
    if (m_worldObject.valid()) {
       if (!m_fired) {
            return m_worldObject->isCrucialVoxelDestroyed();
       }
    } else {
        return !m_fired;
    }
}

void WorldObjectDestroyedPoll::specialOnCallback() {
    EventPoll::specialOnCallback();
    m_fired = true;
    kill();
}

