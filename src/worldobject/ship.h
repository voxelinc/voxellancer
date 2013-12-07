#pragma once

#include <vector>
#include "hardpoint.h"
#include "world/world.h"
#include "world/god.h"

class World;
class God;

class Ship : public WorldObject {
public:
	Ship();
	virtual void update(float deltasec);

    virtual void addHardpointVoxel(HardpointVoxel* voxel);
    void removeHardpoint(Hardpoint *hardpoint);

    void setTargetPoint(glm::vec3 target);
    void setTargetObject(WorldObject* target);
    void fire();
    float minAimDistance();

protected:

    World* m_world;
	std::vector<Hardpoint*> m_hardpoints;
    AimType m_aimMode;
    WorldObject* m_targetObject;
    glm::vec3 m_targetPoint;
};
