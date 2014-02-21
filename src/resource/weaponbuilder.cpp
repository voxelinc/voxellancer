#include "weaponbuilder.h"

#include <string>

#include <glow/logging.h>

#include "equipment/weapon.h"
#include "equipment/weapons/genericgun.h"
#include "equipment/weapons/genericrocketlauncher.h"


WeaponBuilder::WeaponBuilder(const std::string& name):
    m_name(name)
{
}

Weapon* WeaponBuilder::build() {
    /*
        Currently only decides whether the weapons going to be a GenericWeapon
        or a GenericRocketLauncher
    */
    std::string type = Property<std::string>(m_name + ".general.type");

    if (type == "gun") {
        return buildGenericGun();
    } else if(type == "rocketlauncher") {
        return buildGenericRocketLauncher();
    } else {
        glow::fatal("No such weapon '%;'", type);
    }

    return nullptr; // Should never be reached
}

GenericGun* WeaponBuilder::buildGenericGun() {
    GenericGun* gun = new GenericGun(m_name);

    std::string bulletName = Property<std::string>(m_name + ".general.bullet");

    gun->setBulletLifetime(Property<float>(bulletName + ".general.lifetime"));
    gun->setBulletSpeed(Property<float>(bulletName + ".general.speed"));
    gun->setVisuals(Visuals::fromProperties(m_name + ".visuals"));
    gun->setCooldownTime(Property<float>(m_name + ".general.cooldownTime"));
    gun->setBulletName(bulletName);

//    void setBulletPrototype(Bullet* bulletPrototype);

    return gun;
}

GenericRocketLauncher* WeaponBuilder::buildGenericRocketLauncher() {
    GenericRocketLauncher* rocketLauncher = new GenericRocketLauncher(m_name);

    rocketLauncher->setVisuals(Visuals::fromProperties(m_name + ".visuals"));
    rocketLauncher->setCooldownTime(Property<float>(m_name + ".general.cooldownTime"));
    rocketLauncher->setRocketName(Property<std::string>(m_name + ".general.rocket"));

//    void setBulletPrototype(Bullet* bulletPrototype);

    return rocketLauncher;
}

