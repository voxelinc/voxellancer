#pragma once
#include <set>

#include "glm/glm.hpp"

#include "ai/basictask.h"


class Ship;
class WorldObject;

class FlyToTask : public BasicTask {
public:
	FlyToTask(Ship& ship);

	void setTargetPoint(glm::vec3 point);

    virtual void update(float deltaSec);

protected:

	glm::vec3 m_targetPoint;
};

