#pragma once

#include "ai/elevatedtask.h"
#include "worldobject/worldobjecthandle.h"

class Ship;
class BasicTask;


class FollowTask : public ElevatedTask {
public:
    FollowTask(Ship& ship, std::shared_ptr<WorldObjectHandle> target);

    virtual void update(float deltaSec);

protected:
    std::shared_ptr<WorldObjectHandle> m_target;
};

