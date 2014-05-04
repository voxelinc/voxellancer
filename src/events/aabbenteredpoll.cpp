#include "aabbenteredpoll.h"

#include "voxel/voxelclusterbounds.h"

#include "worldobject/worldobject.h"


AABBEnteredPoll::AABBEnteredPoll(WorldObject* worldObject, const AABB& aabb, const Callback& callback):
    EventPoll(callback),
    m_worldObject(makeHandle(worldObject)),
    m_aabb(aabb),
    m_entered(false)
{
}

bool AABBEnteredPoll::isDead() {
    return m_entered || !m_worldObject.valid();
}

bool AABBEnteredPoll::poll() {
    return m_worldObject.valid() ? m_worldObject->bounds().aabb().intersects(m_aabb) : false;
}

void AABBEnteredPoll::specialOnCallback() {
    m_entered = true;
}

