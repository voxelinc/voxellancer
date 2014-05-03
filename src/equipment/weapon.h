#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "display/rendering/visuals.h"

#include "equipment.h"

class Sound;
class Hardpoint;
class Projectile;
class WorldObject;
class SoundProperties;

enum class WeaponType {
    Gun,
    RocketLauncher
};

/**
 * Weapon to be mounted to a Hardpoint
 */
class Weapon: public Equipment {
public:
    Weapon(WeaponType type, const std::string& equipmentKey);

    Hardpoint* hardpoint();
    void setHardpoint(Hardpoint* hardpoint);

    float cooldownTime() const;
    void setCooldownTime(float cooldownTime);

    const Visuals& visuals() const;
    void setVisuals(const Visuals& visuals);

    const std::string projectileName() const;
    void setProjectileName(const std::string& name);

    WeaponType type() const;

    virtual void update(float deltaSec);

    bool canFire();
    void onFired();


protected:
    Hardpoint* m_hardpoint;
    WeaponType m_type;

    float m_cooldown;
    float m_cooldownTime;
    Visuals m_visuals;
    std::string m_projectileName;
};

