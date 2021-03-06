#include "flytotask.h"

#include "worldobject/ship.h"
#include "ai/boardcomputer.h"
#include "utils/simplewayfind.h"


FlyToTask::FlyToTask(BoardComputer* boardComputer) :
    AiTask(boardComputer),
    m_targetPoint(boardComputer->worldObject()->transform().position()),
    m_minDistance(1.0f)
{
}

void FlyToTask::setTargetPoint(const glm::vec3& point, const glm::vec3& up) {
    m_targetPoint = point;
    m_targetUp = up;
}

void FlyToTask::update(float deltaSec) {
    glm::vec3 currentTargetPoint = SimpleWayfind::calculateTravelPoint(*boardComputer()->worldObject(), m_targetPoint);
    boardComputer()->rotateTo(currentTargetPoint, m_targetUp);
    boardComputer()->moveTo(currentTargetPoint);
}

bool FlyToTask::isFinished() {
    return glm::length(boardComputer()->worldObject()->position() - m_targetPoint) < m_minDistance;
}

