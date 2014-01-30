#pragma once

#include "ai/aitask.h"

#include <list>

#include "glm/glm.hpp"

#include "ai/basictasks/flytotask.h"


class Ship;

class PatrolWaypointsTask : public AiTask {
public:
    PatrolWaypointsTask(Ship& ship, std::list<glm::vec3> points);

    virtual void update(float deltaSec) override;

protected:
    FlyToTask m_flyTask;
    std::list<glm::vec3> m_points;
    std::list<glm::vec3>::iterator m_currentPoint;
};

