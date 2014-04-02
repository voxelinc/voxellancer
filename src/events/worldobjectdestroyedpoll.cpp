#include "worldobjectdestroyedpoll.h"

#include "worldobject/worldobject.h"


WorldObjectDestroyedPoll::WorldObjectDestroyedPoll(WorldObject* worldObject, const std::function<void()>& callback) :
    EventPoll(callback),
    m_worldObject(worldObject->handle())
{
}

bool WorldObjectDestroyedPoll::poll() {
    return m_worldObject.valid() == false || m_worldObject->isCrucialVoxelDestroyed() || m_worldObject->areCockpitVoxelsDestroyed();
}

bool WorldObjectDestroyedPoll::isDead() {
    return poll();
}
