#pragma once

#include "worldobject/components/weapon.h"

#include "rocket.h"


/*
    Base class for every Weapon that shoots rockets,
    i.e. projectiles that follow a target
*/
class RocketLauncher: public Weapon {
public:
    RocketLauncher(const std::string& equipmentKey);

    virtual const SoundProps& rocketSound() const = 0;
    virtual const SoundProps& explosionSound() const = 0;

    virtual void fireAtObject(WorldObject* target);

    virtual void update(float deltaSec) override;


protected:
    virtual Rocket* createRocket() = 0;
    void setupRocket(Rocket* rocket, WorldObject* target);
};

