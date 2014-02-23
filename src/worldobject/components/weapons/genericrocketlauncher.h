#pragma once

#include <string>

#include "rocketlauncher.h"


class Rocket;

class GenericRocketLauncher: public RocketLauncher {
public:
    GenericRocketLauncher(const std::string& name);

    virtual Visuals visuals() const override;
    void setVisuals(const Visuals& visuals);

    virtual float cooldownTime() const override;
    void setCooldownTime(float cooldownTime);

    const Rocket* rocketPrototype() const;
    void setRocketPrototype(Rocket* rocketPrototype);

    const std::string& rocketName() const;
    void setRocketName(const std::string& rocketName);


protected:
    float m_cooldownTime;
    Visuals m_visuals;
    std::string m_rocketName;

    virtual Rocket* createRocket() override;
};

