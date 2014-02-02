#pragma once

#include <glm/glm.hpp>

#include "property/property.h"

#include "worldobject/components/weapon.h"


class TorpedoLauncher: public Weapon {
public:
    TorpedoLauncher();

    virtual WeaponAimType aimType() const override;
    virtual float estimatedRange() const override;
    virtual float cooldownTime() const override;

    virtual void shootAtObject(WorldObject* targetObject) override;

    virtual void update(float deltaSec) override;


private:
    Property<float> m_cooldownTime;
    Property<float> m_torpedoLifetime;
    Property<float> m_torpedoTravelspeed;
};

