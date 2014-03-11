#pragma once

#include <functional>

#include "utils/handle/handle.h"

#include "eventpoll.h"


class WorldObjectDestroyedPoll : public EventPoll {
public:
    WorldObjectDestroyedPoll(WorldObject* worldObject, const std::function<void()>& callback);

protected:
    Handle<WorldObject> m_worldObject;
    bool m_isDestroyed;

    virtual bool poll() override;
    virtual bool isDead() const override;

};

