#include "aabbenteredpoll.h"

#include <iostream>

#include "voxel/voxelclusterbounds.h"

#include "worldobject/worldobject.h"


AABBEnteredPoll::AABBEnteredPoll(WorldObject* worldObject, const AABB& aabb, const std::function<void()>& callback):
    EventPoll(callback),
    m_worldObject(worldObject->handle()),
    m_aabb(aabb),
    m_lastEntered(false)
{
    std::cout << "Created Enteredpoll "<<this << std::endl;
}

bool AABBEnteredPoll::poll() {
    bool entered = m_worldObject->bounds().aabb().intersects(m_aabb) && !m_lastEntered;
    m_lastEntered = entered;
    return entered;
}

