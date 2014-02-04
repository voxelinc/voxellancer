#include "genericrocketlauncher.h"

#include "resource/worldobjectfactory.h"

#include "worldobject/components/hardpoint.h"

#include "genericrocket.h"


GenericRocketLauncher::GenericRocketLauncher(const std::string& propertyPrefix):
    RocketLauncher(propertyPrefix),
    GenericEntity(propertyPrefix),
    m_cooldownTime(propertyPrefix + ".general.cooldownTime")
{
}

float GenericRocketLauncher::cooldownTime() const {
    return m_cooldownTime;
}

void GenericRocketLauncher::update(float deltaSec) {
    RocketLauncher::update(deltaSec);
}

Rocket* GenericRocketLauncher::createRocket() {
    GenericRocket* rocket = new GenericRocket(Property<std::string>(propertyPrefix() + ".general.rocket"));
    WorldObjectFactory().equipSomehow(rocket);
    return rocket;
}

