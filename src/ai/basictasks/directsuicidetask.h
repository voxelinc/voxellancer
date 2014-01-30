#pragma once
#include <set>

#include "glm/glm.hpp"

#include "ai/basictask.h"
#include "worldobject/handle/handle.h"


class Ship;
class WorldObject;

class DirectSuicideTask : public BasicTask {
public:
	DirectSuicideTask(Ship& ship, WorldObject* target);

	void setTarget(WorldObject* target);

    virtual void update(float deltaSec);

protected:

	Handle<WorldObject> m_target;
};

