#include "genericgun.h"

#include "genericbullet.h"


GenericGun::GenericGun(const std::string& propertyPrefix):
    Gun(propertyPrefix),
    GenericEntity(propertyPrefix),
    m_cooldownTime(propertyPrefix + ".general.cooldownTime"),
    m_bulletSpeed(Property<std::string>(propertyPrefix + ".general.bullet").get() + ".general.speed"),
    m_bulletLifetime(Property<std::string>(propertyPrefix + ".general.bullet").get() +  ".general.lifetime")
{
}

float GenericGun::cooldownTime() const {
    return m_cooldownTime;
}

float GenericGun::bulletLifetime() const {
    return m_bulletLifetime;
}

float GenericGun::bulletSpeed() const {
    return m_bulletSpeed;
}

Bullet* GenericGun::createBullet() {
    return new GenericBullet(Property<std::string>(propertyPrefix() + ".general.bullet"));
}

