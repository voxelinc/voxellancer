#include "directsuicidetask.h"

#include "worldobject/ship.h"
#include "ai/boardcomputer.h"
#include "utils/geometryhelper.h"


DirectSuicideTask::DirectSuicideTask(Ship& ship, WorldObject* target) :
	AiTask(ship),
	m_target(target ? target->handle() : Handle<WorldObject>(nullptr))
{
}

void DirectSuicideTask::setTarget(WorldObject* target) {
    m_target = (target ? target->handle() : Handle<WorldObject>(nullptr));
}

void DirectSuicideTask::update(float deltaSec) {
    if (m_target.valid()) {
        glm::vec3 targetPoint = m_target->physics().projectedTransformIn(0.1f).position();
        m_ship.boardComputer()->rotateTo(targetPoint);
        glm::vec3 targetDirection = glm::inverse(m_ship.transform().orientation()) * (targetPoint - m_ship.transform().position());
        float angle = GeometryHelper::angleBetween(glm::vec3(0, 0, -1), targetDirection);

        if (angle < glm::radians(15.0f)) {
            m_ship.boardComputer()->moveTo(targetPoint, false);
        } else {
            m_ship.boardComputer()->moveTo(m_ship.transform().position() + m_ship.transform().orientation() * (glm::vec3(0, 0, -70)), true);
        }
    } else {
        m_ship.boardComputer()->moveTo(m_ship.transform().position() + m_ship.transform().orientation() * (glm::vec3(0, 0, -100)), false);
    }
}

