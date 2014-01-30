#pragma once
#include <set>

#include "glm/glm.hpp"

#include "ai/aitask.h"


class Ship;
class WorldObject;

class FlyToTask : public AiTask {
public:
    FlyToTask(Ship& ship);

    void setTargetPoint(const glm::vec3& point);

    virtual void update(float deltaSec) override;


protected:
    glm::vec3 m_targetPoint;
};

