#include "weapon.h"

#include <algorithm>


Weapon::Weapon():
    m_worldObject(nullptr),
    m_coolDown(0.0f),
    m_coolDownTime(0.0f)
{
}

bool Weapon::canFire() {
    return m_coolDown == 0.0f;
}

void Weapon::fired() {
    m_coolDown = m_coolDownTime;
}

float Weapon::coolDownTime() const {
    return m_coolDownTime;
}

void Weapon::setCoolDownTime(float coolDownTime){
    m_coolDownTime = coolDownTime;
}

WorldObject *Weapon::worldObject() {
    return m_worldObject;
}

void Weapon::setWorldObject(WorldObject* worldObject) {
    m_worldObject = worldObject;
}

void Weapon::shootAtPoint(Hardpoint* source, glm::vec3 target) {

}

void Weapon::shootAtObject(Hardpoint* source, WorldObject* target) {

}

void Weapon::update(float deltaSec) {
    m_coolDown = std::max(m_coolDown - deltaSec, 0.0f);
}

