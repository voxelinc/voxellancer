#include "patrolwaypointstask.h"

#include "worldobject/ship.h"
#include "voxel/voxelclusterbounds.h"
#include "ai/formationlogic.h"
#include "ai/basictasks/flytotask.h"
#include "ai/basictasks/formationmembertask.h"

PatrolWaypointsTask::PatrolWaypointsTask(Ship& ship, std::list<glm::vec3> points) :
    AiTask(ship),
    m_points(points),
    m_currentPoint(m_points.begin()),
    m_flyTask(new FlyToTask(ship)),
    m_formationTask(new FormationMemberTask(ship))
{
}

PatrolWaypointsTask::~PatrolWaypointsTask() = default;

void PatrolWaypointsTask::update(float deltaSec) {
    if (m_ship.formationLogic()->inFormation()) {
        m_formationTask->update(deltaSec);
    } else {
        float distance = glm::length(*m_currentPoint - m_ship.transform().position());
        if (distance < m_ship.bounds().sphere().radius()){
            m_currentPoint++;
            if (m_currentPoint == m_points.end()) {
                m_currentPoint = m_points.begin();
            }
        }
        m_flyTask->setTargetPoint(*m_currentPoint);
        m_flyTask->update(deltaSec);
    }
}

