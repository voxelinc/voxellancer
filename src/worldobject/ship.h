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

    void shootAt(glm::vec3 point);
    float minAimDistance();

protected:

    World * m_world;
    std::vector<Hardpoint*> m_hardpoints = std::vector<Hardpoint*>();
};
