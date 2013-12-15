#include "weapon.h"


Weapon::Weapon():
    m_worldObject(nullptr)
{
}

void Weapon::shootAtPoint(Hardpoint* source, glm::vec3 target) {
}

void Weapon::shootAtObject(Hardpoint* source, WorldObject* target) {
}

WorldObject *Weapon::worldObject() {
    return m_worldObject;
}

void Weapon::setWorldObject(WorldObject* worldObject) {
    m_worldObject = worldObject;
}

