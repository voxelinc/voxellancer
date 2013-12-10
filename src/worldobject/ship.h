#pragma once

#include <vector>
#include "worldobject.h"
#include "hardpoint.h"
#include "world/world.h"
#include "world/god.h"
#include "property/propertymanager.h"
#include "property/property.h"

class World;
class God;

class Ship : public WorldObject {
public:
    Ship();
    virtual void update(float deltasec);

    virtual void addHardpointVoxel(HardpointVoxel* voxel);
    void removeHardpoint(Hardpoint *hardpoint);

    void setAimMode(AimType mode);
    AimType aimMode();
    void setTargetPoint(glm::vec3 target);
    glm::vec3 targetPoint();
    void setTargetObject(WorldObject* target);
    WorldObject* targetObject();
    void fire();
    float minAimDistance();

    virtual void accelerate(glm::vec3 direction);
    virtual void accelerateAngular(glm::vec3 axis);

protected:

    Property<float> prop_maxSpeed;
    Property<float> prop_maxRotSpeed;

    World* m_world;
	std::vector<Hardpoint*> m_hardpoints;
    AimType m_aimMode;
    WorldObject* m_targetObject;
    glm::vec3 m_targetPoint;
};
