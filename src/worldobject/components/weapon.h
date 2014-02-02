#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "worldobject/components/worldobjectequipment.h"


class WorldObject;
class Hardpoint;

enum class WeaponAimType {
    None, // nothing attached
    Point, // manual aiming
    Object // guided
};

class Weapon: public WorldObjectEquipment {
public:
    Weapon(const std::string& key);

    Hardpoint* hardpoint();
    void setHardpoint(Hardpoint* hardpoint);

    virtual WeaponAimType aimType() const = 0;
    virtual float estimatedRange() const = 0;
    virtual float cooldownTime() const = 0;

    virtual void shootAtPoint(const glm::vec3& point);
    virtual void shootAtObject(WorldObject* worldObject);

    virtual void update(float deltaSec);

    bool canFire();
    void fired();


protected:
    Hardpoint* m_hardpoint;

    float m_cooldown;
};

