#include "genericrocketlauncher.h"

#include "property/property.h"

#include "rocket.h"


GenericRocketLauncher::GenericRocketLauncher(const std::string& name):
    RocketLauncher(name)
{
}


Visuals GenericRocketLauncher::visuals() const {
    return m_visuals;
}

void GenericRocketLauncher::setVisuals(const Visuals& visuals) {
    m_visuals = visuals;
}

float GenericRocketLauncher::cooldownTime() const {
    return m_cooldownTime;
}

void GenericRocketLauncher::setCooldownTime(float cooldownTime) {
    m_cooldownTime = cooldownTime;
}

const Rocket* GenericRocketLauncher::rocketPrototype() const {
    return m_rocketPrototype.get();
}

void GenericRocketLauncher::setRocketPrototype(Rocket* rocketPrototype) {
    m_rocketPrototype.reset(rocketPrototype);
}

Rocket* GenericRocketLauncher::createRocket() {
    assert(m_rocketPrototype.get());
//    return new Rocket(*m_rocketPrototype.get());
}

