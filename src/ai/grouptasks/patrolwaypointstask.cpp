#include "patrolwaypointstask.h"

#include <glow/logging.h>

#include "worldobject/ship.h"
#include "ai/squadlogic.h"
#include "ai/squad.h"
#include "ai/character.h"
#include "ai/basictasks/flytotask.h"
#include "ai/basictasks/formationmembertask.h"

#include "voxel/voxelclusterbounds.h"


PatrolWaypointsTask::PatrolWaypointsTask(Squad& squad, const std::list<glm::vec3>& points) :
    AiGroupTask(squad),
    m_points(points),
    m_currentPoint(m_points.begin()),
    m_leaderFlyTask(nullptr)
{
    if (m_squad.leader()) {
        onNewLeader(m_squad.leader());
    }
}

PatrolWaypointsTask::PatrolWaypointsTask(Squad& squad):
    PatrolWaypointsTask(squad, {})
{
}

void PatrolWaypointsTask::appendWaypoint(const glm::vec3& point) {
    // m_points needs to be a list to keep the iterator valid!
    m_points.push_back(point);
}

void PatrolWaypointsTask::update(float deltaSec) {
    if (m_squad.leader() && currentTargetPoint() != nullptr) {
        float distance = glm::length(*m_currentPoint - m_squad.leader()->transform().position());
        if (distance < m_squad.leader()->bounds().sphere().radius()){
            ++m_currentPoint;
            if (m_currentPoint == m_points.end()) {
                m_currentPoint = m_points.begin();
            }
        }
        m_leaderFlyTask->setTargetPoint(*m_currentPoint);
        // update called by the leader himself
    }
}

void PatrolWaypointsTask::onNewLeader(Ship* leader) {
    m_leaderFlyTask = std::make_shared<FlyToTask>(leader->boardComputer());
    leader->character()->setTask(m_leaderFlyTask);
}

void PatrolWaypointsTask::onMemberJoin(Ship* member) { std::cout << "Telling " << member <<" to follow" << std::endl;
    member->character()->setTask(std::make_shared<FormationMemberTask>(*member));
}

const glm::vec3* PatrolWaypointsTask::currentTargetPoint() {
    if (m_points.size() == 0) {
        return nullptr;
    } else if (m_currentPoint == m_points.end()) {
        m_currentPoint = m_points.begin();
    }
    return &*m_currentPoint;
}

