#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "worldobject/worldobject.h"


class WorldObject;
class Hardpoint;

// Base class for everything that can be mounted to a Hardpoint
enum AimType {
    None, // nothing attached
    Point, // manual aiming
    Object // guided
};

class Weapon {
public:
    Weapon();

    virtual AimType aimType() = 0; // depending on this, the launcher implements either Point or Object

    virtual void shootAtPoint(Hardpoint* source, glm::vec3 target);
    virtual void shootAtObject(Hardpoint* source, WorldObject* target);

    virtual void update(float deltaSec) = 0;

    virtual float aimRange() = 0;

    WorldObject *worldObject();
    void setWorldObject(WorldObject* worldObject);


protected:
    WorldObject* m_worldObject;
};
