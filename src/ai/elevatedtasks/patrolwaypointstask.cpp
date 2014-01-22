#include "patrolwaypointstask.h"

#include "worldobject/ship.h"

PatrolWaypointsTask::PatrolWaypointsTask(Ship& ship, std::list<glm::vec3> points) :
    ElevatedTask(ship),
    m_points(points),
    m_currentPoint(m_points.begin()),
    m_flyTask(ship)
{
}

void PatrolWaypointsTask::update(float deltaSec) {
    if (glm::length(*m_currentPoint - m_ship.transform().position()) < m_ship.minimalGridSphere().radius() * 0.5){
        m_currentPoint++;
        if (m_currentPoint == m_points.end()) {
            m_currentPoint = m_points.begin();
        }
    }
    m_flyTask.setTargetPoint(*m_currentPoint);
    m_flyTask.update(deltaSec);
}