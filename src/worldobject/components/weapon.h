#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "equipment.h"


class WorldObject;
class Hardpoint;

enum class WeaponType {
    Gun,
    RocketLauncher
};

class Weapon: public Equipment {
public:
    Weapon(WeaponType type, const std::string& equipmentKey);

    Hardpoint* hardpoint();
    void setHardpoint(Hardpoint* hardpoint);

    WeaponType type() const;

    virtual float cooldownTime() const = 0;

    virtual void update(float deltaSec);

    bool canFire();
    void onFired();


protected:
    Hardpoint* m_hardpoint;
    WeaponType m_type;

    float m_cooldown;
};

