#pragma once

#include <vector>
#include "hardpoint.h"
#include "world/world.h"
#include "world/god.h"

class World;
class God;

class Ship : public WorldObject{
public:
	Ship();
	void shootAt(glm::vec3 point);
	virtual void update(float deltasec);
	void addHardpoint(Hardpoint* hardpooint);
    float minAimDistance();

private:
    World * m_world;
	std::vector<Hardpoint*> m_hardpoints = std::vector<Hardpoint*>();
};
