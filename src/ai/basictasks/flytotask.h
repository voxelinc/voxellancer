#pragma once
#include <set>

#include "glm/glm.hpp"

#include "ai/aitask.h"


class BoardComputer;
class WorldObject;

class FlyToTask : public AiTask {
public:
    FlyToTask(BoardComputer* boardComputer);

    const glm::vec3& targetPoint() const;
    void setTargetPoint(const glm::vec3& point, const glm::vec3& up = glm::vec3(0,0,0));

    virtual void update(float deltaSec) override;

    virtual bool isFinished();


protected:
    glm::vec3 m_targetPoint;
    glm::vec3 m_targetUp;
    float m_minDistance;
};

