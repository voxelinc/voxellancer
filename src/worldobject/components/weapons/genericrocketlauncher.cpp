#include "genericrocketlauncher.h"

#include "property/property.h"

#include "resource/worldobjectbuilder.h"

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

const std::string& GenericRocketLauncher::rocketName() const {
    return m_rocketName;
}

void GenericRocketLauncher::setRocketName(const std::string& rocketName) {
    m_rocketName = rocketName;
}

Rocket* GenericRocketLauncher::createRocket() {
    Rocket* rocket = WorldObjectBuilder(m_rocketName).buildRocket();
    return rocket;
}

