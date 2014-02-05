#include "genericgun.h"

#include "genericbullet.h"


GenericGun::GenericGun(const std::string& propertyPrefix):
    Weapon(WeaponType::Gun, propertyPrefix),
    GenericWeapon(WeaponType::Gun, propertyPrefix),
    Gun(propertyPrefix),
    m_bulletSpeed(Property<std::string>(propertyPrefix + ".general.bullet").get() + ".general.speed"),
    m_bulletLifetime(Property<std::string>(propertyPrefix + ".general.bullet").get() +  ".general.lifetime"),
    m_bulletName(Property<std::string>(propertyPrefix + ".general.bullet"))
{
}

float GenericGun::bulletLifetime() const {
    return m_bulletLifetime;
}

float GenericGun::bulletSpeed() const {
    return m_bulletSpeed;
}

Bullet* GenericGun::createBullet() {
    return new GenericBullet(m_bulletName);
}

