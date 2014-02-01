#include "weapon.h"

#include <algorithm>


Weapon::Weapon():
    m_worldObject(nullptr),
    m_cooldown(0.0f)
{
}

Hardpoint* Weapon::hardpoint() {
    return m_hardpoint;
}

void setHardpoint(Hardpoint* hardpoint) {
    m_hardpoint = hardpoint;
}

void Weapon::shootAtPoint(glm::vec3 point) {

}

void Weapon::shootAtObject(WorldObject* worldObject) {

}

void Weapon::update(float deltaSec) {
    m_cooldown = std::max(m_cooldown - deltaSec, 0.0f);
}

bool Weapon::canFire() {
    return m_cooldown == 0.0f;
}

void Weapon::fired() {
    m_coolDown = coolDownTime();
}

