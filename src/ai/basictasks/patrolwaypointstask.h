#pragma once

#include <list>
#include <memory>

#include <glm/glm.hpp>

#include "ai/aitask.h"



class Ship;
class FormationMemberTask;
class FlyToTask;

class PatrolWaypointsTask : public AiTask {
public:
    PatrolWaypointsTask(Ship& ship, std::list<glm::vec3> points);
    virtual ~PatrolWaypointsTask();

    virtual void update(float deltaSec) override;

protected:
    std::unique_ptr<FlyToTask> m_flyTask;
    std::unique_ptr<FormationMemberTask> m_formationTask;
    std::list<glm::vec3> m_points;
    std::list<glm::vec3>::iterator m_currentPoint;
};

