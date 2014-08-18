#include "directsuicidetask.h"

#include "ai/boardcomputer.h"

#include "utils/geometryhelper.h"
#include "physics/physics.h"

#include "worldobject/worldobject.h"


DirectSuicideTask::DirectSuicideTask(BoardComputer* boardComputer, WorldObject* target) :
    AiTask(boardComputer),
    m_target(target ? makeHandle(target) : Handle<WorldObject>())
{
}

void DirectSuicideTask::setTarget(WorldObject* target) {
    m_target = (target ? makeHandle(target) : Handle<WorldObject>());
}

void DirectSuicideTask::update(float deltaSec) {
    WorldObject* worldObject = boardComputer()->worldObject();

    if (m_target.valid()) {
        glm::vec3 targetPoint = m_target->physics().speed().moved(m_target->transform(), 0.1f).position();
        boardComputer()->rotateTo(targetPoint);
        glm::vec3 targetDirection = glm::inverse(worldObject->transform().orientation()) * (targetPoint - worldObject->transform().position());
        float angle = GeometryHelper::angleBetween(glm::vec3(0, 0, -1), targetDirection);

        if (angle < glm::radians(15.0f)) {
            boardComputer()->moveTo(targetPoint, false);
        } else {
            boardComputer()->moveTo(worldObject->transform().position() + worldObject->transform().orientation() * (glm::vec3(0, 0, -70)), true);
        }
    } else {
        boardComputer()->moveTo(worldObject->transform().position() + worldObject->transform().orientation() * (glm::vec3(0, 0, -100)), false);
    }
}


