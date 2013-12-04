#include "hardpoint.h"

#include "ship.h"

Hardpoint::Hardpoint(Ship* ship, const glm::vec3& position, Gun *gun){
    assert(ship != nullptr);
    assert(gun != nullptr);
    m_ship = ship;
	m_position = position;
    m_gun = gun;
}

Bullet* Hardpoint::shootAt(glm::vec3 point){
    return m_gun->shootAt((glm::vec3)(m_ship->transform().applyTo(m_position)), m_ship->transform().orientation(), point);
}

void Hardpoint::update(float deltasec){
    m_gun->update(deltasec);
}

Gun *Hardpoint::gun(){
    return m_gun;
}

void Hardpoint::voxelRemoved(){
    m_ship->removeHardpoint(this);
}