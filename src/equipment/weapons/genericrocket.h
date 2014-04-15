#pragma once

#include <string>

#include "worldobject/genericworldobject.h"

#include "rocket.h"

class SoundProperties;

class GenericRocket: public Rocket {
public:
    GenericRocket();

    virtual const SoundProperties& hitSound() const override;
    void setHitSound(const SoundProperties& hitSound);z

protected:
    SoundProperties m_hitSound;

    virtual void spawnExplosion() override;
    virtual void onLifetimeOver() override;
};

