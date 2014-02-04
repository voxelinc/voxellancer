#pragma once

#include <string>

#include "utils/genericentity.h"

#include "rocketlauncher.h"


class GenericRocketLauncher: public RocketLauncher, public GenericEntity {
public:
    GenericRocketLauncher(const std::string& propertyPrefix);

    virtual float cooldownTime() const override;

    virtual void update(float deltaSec) override;


protected:
    Property<float> m_cooldownTime;

    virtual Rocket* createRocket() override;
};

