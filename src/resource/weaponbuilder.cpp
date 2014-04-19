#include "weaponbuilder.h"

#include <string>

#include <glow/logging.h>

#include "equipment/weapon.h"
#include "equipment/weapons/gun.h"
#include "equipment/weapons/rocketlauncher.h"

#include "property/property.h"


WeaponBuilder::WeaponBuilder(const std::string& name):
    m_name(name)
{
}

Weapon* WeaponBuilder::build() {
    /*
        Currently only decides whether the weapons going to be a Gun
        or a RocketLauncher
    */
    std::string type = Property<std::string>(m_name + ".general.type");

    if (type == "gun") {
        return buildGun();
    } else if(type == "rocketlauncher") {
        return buildRocketLauncher();
    } else {
        glow::fatal("No such weapon '%;'", type);
    }

    return nullptr; // Should never be reached
}

Gun* WeaponBuilder::buildGun() {
    Gun* gun = new Gun(m_name);

    std::string bulletName = Property<std::string>(m_name + ".general.bullet");

    gun->setBulletSpeed(Property<float>(bulletName + ".general.speed"));
    gun->setVisuals(Visuals::fromProperties(m_name + ".visuals"));
    gun->setFireSound(SoundProperties::fromProperties(m_name + ".sound"));
    gun->setCooldownTime(Property<float>(m_name + ".general.cooldownTime"));
    gun->setProjectileName(bulletName);

    return gun;
}

RocketLauncher* WeaponBuilder::buildRocketLauncher() {
    RocketLauncher* rocketLauncher = new RocketLauncher(m_name);

    rocketLauncher->setVisuals(Visuals::fromProperties(m_name + ".visuals"));
    rocketLauncher->setCooldownTime(Property<float>(m_name + ".general.cooldownTime"));
    rocketLauncher->setProjectileName(Property<std::string>(m_name + ".general.rocket"));

    return rocketLauncher;
}

