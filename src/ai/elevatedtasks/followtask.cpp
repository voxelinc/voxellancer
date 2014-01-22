#include "followtask.h"

#include "worldobject/ship.h"
#include "worldobject/worldobjecthandle.h"
#include <list>

FollowTask::FollowTask(Ship& ship, std::shared_ptr<WorldObjectHandle> target) :
    ElevatedTask(ship),
    m_target(target)
{
}

void FollowTask::update(float deltaSec) {
    if (WorldObject* target = m_target->get()) {
        m_ship.boardComputer()->rotateTo(target->transform().position());
        m_ship.boardComputer()->moveTo(target->transform().position() + m_ship.transform().orientation() * glm::vec3(0, 0, 30));
        m_ship.boardComputer()->shootBullet(std::list<std::shared_ptr<WorldObjectHandle>>{m_target});
    }
}