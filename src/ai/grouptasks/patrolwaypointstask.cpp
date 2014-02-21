#include "patrolwaypointstask.h"

#include "worldobject/ship.h"
#include "ai/squadlogic.h"
#include "ai/squad.h"
#include "ai/character.h"
#include "ai/basictasks/formationmembertask.h"
#include "voxel/voxelclusterbounds.h"


PatrolWaypointsTask::PatrolWaypointsTask(Squad& squad, std::list<glm::vec3> points) :
    AiGroupTask(squad),
    m_points(points),
    m_currentPoint(m_points.begin()),
    m_leaderFlyTask(nullptr)
{
    if (m_squad.leader()) {
        onNewLeader(m_squad.leader());
    }
}

void PatrolWaypointsTask::update(float deltaSec) {
    if (m_squad.leader()) {
        float distance = glm::length(*m_currentPoint - m_squad.leader()->transform().position());
        if (distance < m_squad.leader()->bounds().sphere().radius()){
            m_currentPoint++;
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

void PatrolWaypointsTask::onMemberJoin(Ship* member) {
    member->character()->setTask(std::make_shared<FormationMemberTask>(*member));
}
