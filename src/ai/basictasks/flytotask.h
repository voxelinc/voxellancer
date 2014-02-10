#pragma once
#include <set>

#include "glm/glm.hpp"

#include "ai/aitask.h"


class Ship;
class WorldObject;

class FlyToTask : public AiTask {
public:
    FlyToTask(Ship& ship);

    void setTargetPoint(const glm::vec3& point, const glm::vec3& up = glm::vec3(0,0,0));

    virtual void update(float deltaSec) override;


protected:
    glm::vec3 m_targetPoint;
    glm::vec3 m_targetUp;
};

