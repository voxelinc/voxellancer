#pragma once

#include <string>

#include "utils/genericentity.h"

#include "worldobject/genericworldobject.h"

#include "rocket.h"


class GenericRocket: public GenericWorldObject, public Rocket {
public:
    GenericRocket(const std::string& propertyPrefix);


protected:
    virtual void spawnExplosion() override;
    virtual void onLifetimeOver() override;
};

