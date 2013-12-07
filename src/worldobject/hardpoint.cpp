#include "hardpoint.h"

#include "ship.h"

Hardpoint::Hardpoint(Ship* ship, const glm::vec3& position, Launcher *launcher){
    assert(ship != nullptr);
    m_ship = ship;
	m_position = position;
    m_launcher = launcher;
}

Hardpoint::~Hardpoint(){
    if (m_launcher) delete m_launcher;
}

void Hardpoint::setLauncher(Launcher *launcher){
    m_launcher = launcher;
}

Launcher* Hardpoint::launcher(){
    return m_launcher;
}

void Hardpoint::update(float delta_sec){
    if (m_launcher)
        m_launcher->update(delta_sec);
}

AimType Hardpoint::aimType(){
    if (m_launcher)
        return m_launcher->aimType();
    else
        return AimType::None;
}
void Hardpoint::shootAtPoint(glm::vec3 target){
    if (m_launcher)
        m_launcher->shootAtPoint((glm::vec3)(m_ship->transform().applyTo(m_position)), m_ship->transform().orientation(), target);
}
void Hardpoint::shootAtObject(WorldObject* target){
    if (m_launcher)
        m_launcher->shootAtObject((glm::vec3)(m_ship->transform().applyTo(m_position)), m_ship->transform().orientation(), target);
}

float Hardpoint::aimRange(){
    if (m_launcher)
        return m_launcher->aimRange();
    else
        return -1;
}

void Hardpoint::voxelRemoved(){
    m_ship->removeHardpoint(this);
}