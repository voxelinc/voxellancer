#include "directsuicidetask.h"

#include "worldobject/ship.h"
#include "ai/boardcomputer.h"
#include "utils/geometryhelper.h"


DirectSuicideTask::DirectSuicideTask(Ship& ship, WorldObject* target) :
	BasicTask(ship),
	m_target(target ? target->handle() : Handle<WorldObject>(nullptr))
{
}

void DirectSuicideTask::setTarget(WorldObject* target) {
    m_target = (target ? target->handle() : Handle<WorldObject>(nullptr));
}

void DirectSuicideTask::update(float deltaSec) {
    if (m_target.valid()) {
        glm::vec3 targetPoint = m_target->physics().projectedTransformIn(0.5f).position();
        m_ship.boardComputer()->rotateTo(targetPoint); // , m_ship.transform().orientation() * glm::vec3(1, 0, 0));
        glm::vec3 targetDirection = m_ship.transform().inverseApplyTo(targetPoint);
        float angle = GeometryHelper::angleBetween(glm::vec3(0, 0, -1), targetDirection);

        if (angle < glm::radians(10.0f)) {
            m_ship.boardComputer()->moveTo(targetPoint, false);
        } else {
            m_ship.boardComputer()->moveTo(m_ship.transform().applyTo(glm::vec3(0, 0, -100)), true);
        }
    } else {
        m_ship.boardComputer()->moveTo(m_ship.transform().applyTo(glm::vec3(0, 0, -100)), false);
    }
}
