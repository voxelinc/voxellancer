#include "aabbenteredpoll.h"

#include "voxel/voxelclusterbounds.h"

#include "worldobject/worldobject.h"


AABBEnteredPoll::AABBEnteredPoll(WorldObject* worldObject, const AABB& aabb, const std::function<void()>& callback):
    EventPoll(callback),
    m_worldObject(worldObject->handle()),
    m_aabb(aabb),
    m_lastEntered(false)
{
}

void AABBEnteredPoll::update(float deltaSec) {
    bool entered = m_worldObject->bounds().aabb().intersects(m_aabb);
    if (entered && !m_lastEntered) {
        m_callback();
    }
    m_lastEntered = entered;
}

