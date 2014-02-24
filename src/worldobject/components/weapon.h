#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "equipment.h"

class Sound;
class Hardpoint;
class Projectile;
class WorldObject;
class Visuals;
class SoundProperties;

enum class WeaponType {
    Gun,
    RocketLauncher
};

class Weapon: public Equipment {
public:
    Weapon(WeaponType type, const std::string& equipmentKey);

    virtual const Visuals& visuals() const = 0;

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

