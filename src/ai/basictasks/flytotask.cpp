#include "flytotask.h"

#include "worldobject/ship.h"
#include "ai/boardcomputer.h"
#include "utils/simplewayfind.h"


FlyToTask::FlyToTask(Ship& ship) :
	AiTask(ship),
	m_targetPoint(ship.transform().position())
{
}

void FlyToTask::setTargetPoint(const glm::vec3& point, const glm::vec3& up) {
	m_targetPoint = point;
    m_targetUp = up;
}

void FlyToTask::update(float deltaSec) {
	glm::vec3 currentTargetPoint = SimpleWayfind::calculateTravelPoint(m_ship, m_targetPoint);
    m_ship.boardComputer()->rotateTo(currentTargetPoint, m_targetUp);
    m_ship.boardComputer()->moveTo(currentTargetPoint);
}
