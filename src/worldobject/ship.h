#pragma once

#include <vector>
#include "worldobject.h"
#include "world/world.h"
#include "world/god.h"
#include "property/propertymanager.h"
#include "property/property.h"

class World;
class God;
class Hardpoint;

class Ship : public WorldObject {
public:
    Ship();
    virtual void update(float deltasec);

    virtual void addHardpointVoxel(HardpointVoxel* voxel);
    void removeHardpoint(Hardpoint *hardpoint);

    void setTargetObject(WorldObject* target);
    WorldObject* targetObject();
    void fireAtPoint(glm::vec3 target);
    void fireAtObject();
    float minAimDistance();

    virtual void accelerate(glm::vec3 direction);
    virtual void accelerateAngular(glm::vec3 axis);

protected:

    Property<float> prop_maxSpeed;
    Property<float> prop_maxRotSpeed;

    World* m_world;
	std::vector<Hardpoint*> m_hardpoints;
    WorldObject* m_targetObject;
};
