#include "worldobjectdestroyedpoll.h"

#include "worldobject/worldobject.h"


WorldObjectDestroyedPoll::WorldObjectDestroyedPoll(WorldObject* worldObject, const Callback& callback):
    EventPoll(callback),
    m_worldObject(makeHandle(worldObject))
{
}

bool WorldObjectDestroyedPoll::poll() {
    return !m_worldObject.valid() || m_worldObject->isCrucialVoxelDestroyed();
}

bool WorldObjectDestroyedPoll::isDead() {
    return poll();
}

