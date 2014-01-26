#include "flytotask.h"

#include "worldobject/ship.h"
#include "utils/simplewayfind.h"


FlyToTask::FlyToTask(Ship& ship) :
	BasicTask(ship),
	m_targetPoint(ship.transform().position())
{
}

void FlyToTask::setTargetPoint(const glm::vec3& point) {
	m_targetPoint = point;
}

void FlyToTask::update(float deltaSec) {
	glm::vec3 currentTargetPoint = SimpleWayfind::calculateTravelPoint(m_ship, m_targetPoint);
    m_ship.boardComputer()->rotateTo(currentTargetPoint);
    m_ship.boardComputer()->moveTo(currentTargetPoint);
}
