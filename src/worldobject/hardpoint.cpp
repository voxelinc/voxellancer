#include "hardpoint.h"

Hardpoint::Hardpoint(glm::vec3 position, Gun *gun){
	m_position = position;
    m_gun = gun;
}

Bullet* Hardpoint::shoot(glm::vec3 shipPosition, glm::vec3 dir){
    return m_gun->shoot(shipPosition + m_position, dir);
}

Bullet* Hardpoint::shoot(glm::mat4 shipMatrix, glm::vec3 dir){
    return m_gun->shoot((glm::vec3)(shipMatrix * glm::vec4(m_position,1.0)), dir);
}

void Hardpoint::update(float deltasec){
    m_gun->update(deltasec);
}