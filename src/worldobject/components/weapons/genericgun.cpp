#include "genericgun.h"

#include "resource/worldobjectbuilder.h"

#include "genericbullet.h"


GenericGun::GenericGun(const std::string& name):
    Gun(name)
{
}

float GenericGun::bulletLifetime() const {
    return m_bulletLifetime;
}

void GenericGun::setBulletLifetime(float bulletLifetime) {
    m_bulletLifetime = bulletLifetime;
}

float GenericGun::bulletSpeed() const {
    return m_bulletSpeed;
}

void GenericGun::setBulletSpeed(float bulletSpeed) {
    m_bulletSpeed = bulletSpeed;
}

Visuals GenericGun::visuals() const {
    return m_visuals;
}

void GenericGun::setVisuals(const Visuals& visuals) {
    m_visuals = visuals;
}

float GenericGun::cooldownTime() const {
    return m_cooldownTime;
}

void GenericGun::setCooldownTime(float cooldownTime) {
    m_cooldownTime = cooldownTime;
}

const std::string& GenericGun::bulletName() const {
    return m_bulletName;
}

void GenericGun::setBulletName(const std::string& bulletName) {
    m_bulletName = bulletName;
}

Bullet* GenericGun::createBullet() {
    return WorldObjectBuilder(m_bulletName).buildBullet();
}

