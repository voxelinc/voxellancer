#pragma once

#include "worldobject/components/weapon.h"

#include "rocket.h"


/*
    Base class for every Weapon that shoots rockets,
    i.e. projectiles that follow a target
*/
class RocketLauncher: virtual public Weapon {
public:
    RocketLauncher(const std::string& equipmentKey);

    virtual void fireAtObject(WorldObject* target);

    virtual void update(float deltaSec) override;


protected:
    virtual Rocket* createRocket() = 0;
    void setupRocket(Rocket* rocket, WorldObject* target);
};

