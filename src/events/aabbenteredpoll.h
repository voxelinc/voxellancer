#pragma once

#include <functional>

#include "geometry/aabb.h"

#include "utils/handle/handle.h"

#include "eventpoll.h"


class AABBEnteredPoll : public EventPoll {
public:
    AABBEnteredPoll(WorldObject* worldObject, const AABB& aabb, const std::shared_ptr<Callback>& callback);


protected:
    Handle<WorldObject> m_worldObject;
    AABB m_aabb;

    bool m_lastEntered;


    virtual bool poll() override;
};

