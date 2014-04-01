#include "aabbenteredpoll.h"

#include "voxel/voxelclusterbounds.h"

#include "worldobject/worldobject.h"


AABBEnteredPoll::AABBEnteredPoll(WorldObject* worldObject, const AABB& aabb, const std::function<void()>& callback):
    EventPoll(callback),
    m_worldObject(worldObject->handle()),
    m_aabb(aabb),
    m_entered(false)
{
}

bool AABBEnteredPoll::isDead() {
    return m_entered;
}

bool AABBEnteredPoll::poll() {
    return m_worldObject->bounds().aabb().intersects(m_aabb);
}

void AABBEnteredPoll::specialOnCallback() {
    m_entered = true;
}
