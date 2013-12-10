#include "hardpoint.h"

#include "ship.h"

Hardpoint::Hardpoint(Ship* ship, const glm::vec3& positionInGrid, Weapon *weapon){
    assert(ship != nullptr);
    m_ship = ship;
    m_positionInGrid = positionInGrid;
    m_weapon = weapon;
}

Hardpoint::~Hardpoint(){
    if (m_weapon) delete m_weapon;
}

void Hardpoint::setWeapon(Weapon *launcher){
    m_weapon = launcher;
}

Weapon* Hardpoint::weapon(){
    return m_weapon;
}

glm::vec3 Hardpoint::position(){
    return m_ship->transform().applyTo(m_positionInGrid);
}
Ship* Hardpoint::ship(){
    return m_ship;
}

void Hardpoint::update(float delta_sec){
    if (m_weapon)
        m_weapon->update(delta_sec);
}

AimType Hardpoint::aimType(){
    if (m_weapon)
        return m_weapon->aimType();
    else
        return AimType::None;
}
void Hardpoint::shootAtPoint(glm::vec3 target){
    if (m_weapon)
        m_weapon->shootAtPoint(this, target);
}
void Hardpoint::shootAtObject(WorldObject* target){
    if (m_weapon)
        m_weapon->shootAtObject(this, target);
}

float Hardpoint::aimRange(){
    if (m_weapon)
        return m_weapon->aimRange();
    else
        return -1;
}

void Hardpoint::voxelRemoved(){
    m_ship->removeHardpoint(this);
}
