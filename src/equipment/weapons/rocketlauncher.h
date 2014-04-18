#pragma once

#include "display/rendering/visuals.h"

#include "equipment/weapon.h"

#include "sound/soundproperties.h"

#include "rocket.h"


/**
 *   Base class for every Weapon that shoots rockets,
 *   i.e. projectiles that follow a target
*/
class RocketLauncher: public Weapon {
public:
    RocketLauncher(const std::string& equipmentKey);

    const Visuals& visuals() const;
    void setVisuals(const Visuals& visuals);

    float cooldownTime() const;
    void setCooldownTime(float cooldownTime);

    const std::string& rocketName() const;
    void setRocketName(const std::string& rocketName);

    void fireAtObject(WorldObject* target);

    void update(float deltaSec) override;


protected:
    Rocket* createRocket();
    void setupRocket(Rocket* rocket, WorldObject* target);


protected:
    float m_cooldownTime;
    SoundProperties m_rocketSound;
    SoundProperties m_explosionSound;
    Visuals m_visuals;
    std::string m_rocketName;
};

