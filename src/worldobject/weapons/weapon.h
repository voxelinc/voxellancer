#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

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
    virtual AimType aimType() = 0; // depending on this, the launcher implements either Point or Object
    virtual void shootAtPoint(Hardpoint* source, glm::vec3 target);
    virtual void shootAtObject(Hardpoint* source, WorldObject* target);
    virtual void update(float delta_sec) = 0;
    virtual float aimRange() = 0;

};