#include "genericrocketlauncher.h"

#include "resource/worldobjectfactory.h"

#include "worldobject/components/hardpoint.h"

#include "genericrocket.h"


GenericRocketLauncher::GenericRocketLauncher(const std::string& propertyPrefix):
    Weapon(WeaponType::RocketLauncher, propertyPrefix),
    GenericWeapon(WeaponType::RocketLauncher, propertyPrefix),
    RocketLauncher(propertyPrefix)
{
}

void GenericRocketLauncher::update(float deltaSec) {
    RocketLauncher::update(deltaSec);
}

Rocket* GenericRocketLauncher::createRocket() {
    GenericRocket* rocket = new GenericRocket(Property<std::string>(propertyPrefix() + ".general.rocket"));
    WorldObjectFactory().equipSomehow(rocket);
    return rocket;
}

