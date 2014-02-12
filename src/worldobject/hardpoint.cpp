#include "hardpoint.h"

#include "ship.h"
#include "weapons/weapon.h"

Hardpoint::Hardpoint(Ship* ship, const glm::ivec3& positionInGrid, std::shared_ptr<Weapon> weapon) {
    assert(ship != nullptr);
    m_ship = ship;
    m_positionInGrid = glm::vec3(positionInGrid);
    installWeapon(weapon);
}

Hardpoint::~Hardpoint() {

}

void Hardpoint::installWeapon(std::shared_ptr<Weapon> launcher) {
    m_weapon = launcher;
    m_weapon->setWorldObject(m_ship);
}

Weapon* Hardpoint::weapon() {
    return m_weapon.get();
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

float Hardpoint::range(){
    if (m_weapon) {
        return m_weapon->range();
    } else {
        return -1;
    }
}

void Hardpoint::voxelRemoved(){
    m_ship->removeHardpoint(this);
}

