#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class WorldObject;
class Hardpoint;

// Base class for everything that can be mounted to a Hardpoint
enum class AimType {
    None, // nothing attached
    Point, // manual aiming
    Object // guided
};

class Weapon {
public:
    Weapon();

    virtual AimType aimType() = 0; // depending on this, the launcher implements either Point or Object

    virtual float bulletSpeed() const = 0;

    bool canFire();
    void fired();

    float coolDownTime() const;
    void setCoolDownTime(float coolDownTime);

    virtual float range() = 0;

    WorldObject *worldObject();
    void setWorldObject(WorldObject* worldObject);

    virtual void shootAtPoint(Hardpoint* source, glm::vec3 target);
    virtual void shootAtObject(Hardpoint* source, WorldObject* target);

    virtual void update(float deltaSec);


protected:
    WorldObject* m_worldObject;

    float m_coolDown;
    float m_coolDownTime;
};
