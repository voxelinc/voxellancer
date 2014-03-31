#include "aabbenteredpoll.h"

#include "voxel/voxelclusterbounds.h"

#include "worldobject/worldobject.h"


AABBEnteredPoll::AABBEnteredPoll(WorldObject* worldObject, const AABB& aabb, const std::shared_ptr<Callback>& callback):
    EventPoll(callback),
    m_worldObject(worldObject->handle()),
    m_aabb(aabb),
    m_lastEntered(false)
{
}

bool AABBEnteredPoll::poll() {
    bool entered = m_worldObject->bounds().aabb().intersects(m_aabb);
    bool result = entered && !m_lastEntered;
    m_lastEntered = entered;
    return result;
}

