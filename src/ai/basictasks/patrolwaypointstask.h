#pragma once

#include "ai/aitask.h"

#include <list>

#include "glm/glm.hpp"

#include "ai/basictasks/flytotask.h"
#include "ai/basictasks/formationmembertask.h"


class Ship;

class PatrolWaypointsTask : public AiTask {
public:
    PatrolWaypointsTask(Ship& ship, std::list<glm::vec3> points);

    virtual void update(float deltaSec) override;

protected:
    FlyToTask m_flyTask;
    Ship& m_ship;
    FormationMemberTask m_formationTask;
    std::list<glm::vec3> m_points;
    std::list<glm::vec3>::iterator m_currentPoint;
};

