#pragma once

#include <functional>

#include "geometry/aabb.h"

#include "worldobject/handle/handle.h"

#include "eventpoll.h"


class AABBEnteredPoll : public EventPoll {
public:
    AABBEnteredPoll(WorldObject* worldObject, const AABB& aabb, const std::function<void()>& callback);

    virtual void update(float deltaSec);


protected:
    Handle<WorldObject> m_worldObject;
    AABB m_aabb;

    bool m_lastEntered;
};

