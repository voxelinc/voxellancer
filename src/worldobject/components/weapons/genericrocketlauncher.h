#pragma once

#include <string>

#include "utils/genericentity.h"

#include "genericweapon.h"
#include "rocketlauncher.h"


class GenericRocketLauncher: public GenericWeapon, public RocketLauncher {
public:
    GenericRocketLauncher(const std::string& propertyPrefix);

    virtual void update(float deltaSec) override;


protected:
    virtual Rocket* createRocket() override;
};

