#include "worldobjectdestroyedpoll.h"

#include "worldobject/worldobject.h"


WorldObjectDestroyedPoll::WorldObjectDestroyedPoll(WorldObject* worldObject, const Callback& callback):
    EventPoll(callback),
    m_worldObject(worldObject->handle())
{
}

bool WorldObjectDestroyedPoll::poll() {
    return m_worldObject.valid() == false || m_worldObject->isCrucialVoxelDestroyed();
}

bool WorldObjectDestroyedPoll::isDead() {
    return poll();
}
