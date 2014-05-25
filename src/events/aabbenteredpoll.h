#pragma once

#include <functional>

#include "geometry/aabb.h"

#include "utils/handle/handle.h"

#include "eventpoll.h"


class AABBEnteredPoll : public EventPoll {
public:
    AABBEnteredPoll(WorldObject* worldObject, const AABB& aabb, const Callback& callback);


protected:
    Handle<WorldObject> m_worldObject;
    AABB m_aabb;

    bool m_entered;

    virtual bool poll() override;
    virtual void specialOnCallback() override;

    virtual void doSpawn() override;
    virtual void doUnspawn() override;
};

