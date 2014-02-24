#pragma once

#include <string>

#include "worldobject/genericworldobject.h"

#include "rocket.h"

class SoundProperties;

class GenericRocket: public Rocket {
public:
    GenericRocket();


protected:
    virtual void spawnExplosion() override;
    virtual void onLifetimeOver() override;
};

