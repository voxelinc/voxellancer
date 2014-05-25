#include "aabbenteredpoll.h"

#include <iostream>

#include "universe/sector.h"

#include "voxel/voxelclusterbounds.h"

#include "worldobject/worldobject.h"


AABBEnteredPoll::AABBEnteredPoll(WorldObject* worldObject, const AABB& aabb, const Callback& callback):
    EventPoll(callback),
    m_worldObject(makeHandle(worldObject)),
    m_aabb(aabb),
    m_entered(false)
{
}

bool AABBEnteredPoll::poll() {
    if (m_worldObject.valid()) {
        return !m_entered && m_worldObject->bounds().aabb().intersects(m_aabb);
    } else {
        unspawn();
        return false;
    }
}

void AABBEnteredPoll::specialOnCallback() {
    EventPoll::specialOnCallback();
    m_entered = true;
}

void AABBEnteredPoll::doSpawn() {
    assert(sector());
    sector()->addFunctionalObject(this);
}

void AABBEnteredPoll::doUnspawn() {
    assert(sector());
    sector()->removeFunctionalObject(this);
}

