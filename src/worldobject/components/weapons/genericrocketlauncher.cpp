#include "genericrocketlauncher.h"

#include "property/property.h"

#include "resource/worldobjectbuilder.h"

#include "rocket.h"


GenericRocketLauncher::GenericRocketLauncher(const std::string& name):
    RocketLauncher(name)
{
}

const Visuals& GenericRocketLauncher::visuals() const {
    return m_visuals;
}

void GenericRocketLauncher::setVisuals(const Visuals& visuals) {
    m_visuals = visuals;
}

const SoundProps& GenericRocketLauncher::rocketSound() const {
    return m_rocketSound;
}

void GenericRocketLauncher::setRocketSound(const SoundProps& rocketSound) {
    m_rocketSound = rocketSound;
}

const SoundProps& GenericRocketLauncher::explosionSound() const {
    return m_explosionSound;
}

void GenericRocketLauncher::setExplosionSound(const SoundProps& explosionSound) {
    m_explosionSound = explosionSound;
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


