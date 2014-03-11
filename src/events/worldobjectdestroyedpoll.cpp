#include "worldobjectdestroyedpoll.h"

#include <iostream>

#include "voxel/voxelclusterbounds.h"

#include "worldobject/worldobject.h"


WorldObjectDestroyedPoll::WorldObjectDestroyedPoll(WorldObject* worldObject, const std::function<void()>& callback) :
    EventPoll(callback),
    m_worldObject(worldObject->handle()),
    m_isDestroyed(poll())
{
}

bool WorldObjectDestroyedPoll::poll() {
    m_isDestroyed = m_worldObject.valid() && m_worldObject->isDestroyed();
    return m_isDestroyed;
}


bool WorldObjectDestroyedPoll::isDead() const {
    return m_isDestroyed;
}
