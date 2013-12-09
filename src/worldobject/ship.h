#pragma once

#include <vector>
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

    void shootAt(glm::vec3 point);
    float minAimDistance();

    virtual void accelerate(glm::vec3 direction);
    virtual void accelerateAngular(glm::vec3 axis);

protected:

    Property<float> prop_maxSpeed;
    Property<float> prop_maxRotSpeed;

    World * m_world;
    std::vector<Hardpoint*> m_hardpoints = std::vector<Hardpoint*>();
};
