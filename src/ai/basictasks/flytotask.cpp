#include "flytotask.h"

#include "worldobject/ship.h"
#include "geometry/line.h"
#include "worldtree/worldtreequery.h"

FlyToTask::FlyToTask(Ship& ship) :
	BasicTask(ship),
	m_targetPoint(ship.transform().position())
{
}

void FlyToTask::setTargetPoint(glm::vec3 point) {
	m_targetPoint = point;
}

void FlyToTask::update(float deltaSec) {
	glm::vec3 currentTargetPoint = calculateTargetPoint();
    m_ship.boardComputer()->rotateTo(currentTargetPoint);
    m_ship.boardComputer()->moveTo(currentTargetPoint);
}

glm::vec3 FlyToTask::calculateTargetPoint() {
    //TODO: don't just check the line from center to center, consider own size
    Line mainLine(m_ship.transform().position(), m_targetPoint);
    WorldTreeQuery mainQuery(&World::instance()->worldTree(), &mainLine);
    std::set<WorldObject*> obstacles = mainQuery.intersectingWorldObjects();
    if (obstacles.size() > 1) {
        WorldObject* obstacle = closestObjectExceptSelf(&obstacles);
        if (obstacle) {
            return calculateEvasionPointFor(obstacle);
        } else {
            return m_targetPoint;
        }
    } else {
        return m_targetPoint;
    }
}

glm::vec3 FlyToTask::calculateEvasionPointFor(WorldObject* obstacle) {
	// look at the boundingSphere and take the shortest way around it
	glm::vec3 toTarget = m_targetPoint - m_ship.transform().position();
	glm::vec3 toObject = obstacle->transform().position() - m_ship.transform().position();
	float dotP = glm::dot(toTarget, toObject);
	float cosAlpha = dotP / (glm::length(toTarget) * glm::length(toObject));
	glm::vec3 crossPoint = m_ship.transform().position() + (glm::normalize(toTarget) * cosAlpha * glm::length(toObject));
	glm::vec3 evasionDirection = glm::normalize(crossPoint - obstacle->transform().position());
	float evasionDistance = obstacle->minimalGridSphere().radius() + m_ship.minimalGridSphere().radius();
	return obstacle->transform().position() + evasionDirection * evasionDistance;
}

WorldObject* FlyToTask::closestObjectExceptSelf(std::set<WorldObject*>* objects){
	WorldObject* closestObject = nullptr;
	float closestDistance = -1;

	for (WorldObject* object : *objects) {
		float distance = glm::length(object->transform().position() - m_ship.transform().position());
		if ((closestDistance == -1 || distance < closestDistance) && object != &m_ship){
			closestDistance = distance;
			closestObject = object;
		}
	}
	return closestObject;
}