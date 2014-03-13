#pragma once

#include "ai/aigrouptask.h"

#include <list>

#include "glm/glm.hpp"

#include "ai/basictasks/flytotask.h"


class Squad;

class PatrolWaypointsTask : public AiGroupTask {
public:
    PatrolWaypointsTask(Squad& squad, std::list<glm::vec3> points = {});

    void appendWaypoint(const glm::vec3& point);

    virtual void update(float deltaSec) override;

    const glm::vec3* currentTargetPoint();

protected:
    virtual void onNewLeader(Ship* leader) override;
    virtual void onMemberJoin(Ship* member) override;

    std::shared_ptr<FlyToTask> m_leaderFlyTask;
    std::list<glm::vec3> m_points;
    std::list<glm::vec3>::iterator m_currentPoint;
};

