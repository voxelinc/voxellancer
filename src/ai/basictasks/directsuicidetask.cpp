#include "directsuicidetask.h"

#include "worldobject/ship.h"
#include "utils/geometryhelper.h"


DirectSuicideTask::DirectSuicideTask(Ship& ship, WorldObject* target) :
	BasicTask(ship),
	m_target(target ? target->handle() : WorldObjectHandle::nullHandle())
{
}

void DirectSuicideTask::setTarget(WorldObject* target) {
    m_target = (target ? target->handle() : WorldObjectHandle::nullHandle());
}

void DirectSuicideTask::update(float deltaSec) {
    if (m_target->get()) {
        glm::vec3 targetPoint = m_target->get()->physics().projectedTransformIn(1.0f).position();
        m_ship.boardComputer()->rotateTo(targetPoint); // , m_ship.transform().orientation() * glm::vec3(1, 0, 0));
        glm::vec3 targetDirection = m_ship.transform().inverseApplyTo(targetPoint);
        float angle = GeometryHelper::angleBetween(glm::vec3(0, 0, -1), targetDirection);
        if (angle < glm::radians(10.0f)) {
            m_ship.boardComputer()->moveTo(targetPoint, false);
        } else {
            m_ship.boardComputer()->moveTo(m_ship.transform().applyTo(glm::vec3(0, 0, -100)), false);
        }
    }
}
