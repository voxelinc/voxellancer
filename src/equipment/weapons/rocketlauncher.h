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

    void fireAtObject(WorldObject* target);

    void update(float deltaSec) override;


protected:
    void setupRocket(Rocket* rocket, WorldObject* target);


protected:
    SoundProperties m_rocketSound;
    SoundProperties m_explosionSound;
};

