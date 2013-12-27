#include "hardpoint.h"

#include "ship.h"

Hardpoint::Hardpoint(Ship* ship, const glm::ivec3& positionInGrid, Weapon *weapon) {
    assert(ship != nullptr);
    m_ship = ship;
    m_positionInGrid = glm::vec3(positionInGrid);
    installWeapon(weapon);
}

Hardpoint::~Hardpoint() {
    delete m_weapon;
}

void Hardpoint::installWeapon(Weapon *launcher) {
    m_weapon = launcher;
    m_weapon->setWorldObject(m_ship);
}

Weapon* Hardpoint::weapon() {
    return m_weapon;
}

glm::vec3 Hardpoint::position() {
    return m_ship->transform().applyTo(m_positionInGrid);
}

Ship* Hardpoint::ship() {
    return m_ship;
}

void Hardpoint::update(float deltaSec) {
    if (m_weapon != nullptr) {
        m_weapon->update(deltaSec);
    }
}

AimType Hardpoint::aimType() {
    if (m_weapon != nullptr) {
        return m_weapon->aimType();
    } else {
        return AimType::None;
    }
}
void Hardpoint::shootAtPoint(glm::vec3 target){
    if (m_weapon) {
        m_weapon->shootAtPoint(this, target);
    }
}

void Hardpoint::shootAtObject(WorldObject* target){
    if (m_weapon) {
        m_weapon->shootAtObject(this, target);
    }
}

float Hardpoint::aimRange(){
    if (m_weapon) {
        return m_weapon->aimRange();
    } else {
        return -1;
    }
}

void Hardpoint::voxelRemoved(){
    m_ship->removeHardpoint(this);
}

