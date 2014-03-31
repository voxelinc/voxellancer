#pragma once

#include <functional>

#include "utils/handle/handle.h"

#include "eventpoll.h"


class WorldObjectDestroyedPoll : public EventPoll {
public:
    WorldObjectDestroyedPoll(WorldObject* worldObject, const std::shared_ptr<Callback>& callback);

protected:
    Handle<WorldObject> m_worldObject;

    virtual bool poll() override;
    virtual bool isDead() override;

};

