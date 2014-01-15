#include "followtask.h"

#include "worldobject/ship.h"
#include "worldobject/worldobjecthandle.h"

FollowTask::FollowTask(Ship& ship, std::shared_ptr<WorldObjectHandle> target) :
    ElevatedTask(ship),
    m_target(target)
{
}

void FollowTask::update(float deltaSec) {
    if (WorldObject* target = m_target->get()) {
        //m_ship.boardComputer()->rotateTo(target->transform().position());
        m_ship.boardComputer()->moveTo(target->transform().position(), 30);
    }
}