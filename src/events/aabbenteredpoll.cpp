#include "aabbenteredpoll.h"

#include "voxel/voxelclusterbounds.h"

#include "worldobject/worldobject.h"


AABBEnteredPoll::AABBEnteredPoll(WorldObject* worldObject, const AABB& aabb, const Callback& callback):
    EventPoll(callback),
    m_worldObject(worldObject->handle()),
    m_aabb(aabb),
    m_entered(false)
{
}

bool AABBEnteredPoll::isDead() {
    return m_entered || !m_worldObject.valid();
}

bool AABBEnteredPoll::poll() {
    if (m_worldObject.valid()) {
        return m_worldObject->bounds().aabb().intersects(m_aabb);
    }
    return false;
}

void AABBEnteredPoll::specialOnCallback() {
    m_entered = true;
}

