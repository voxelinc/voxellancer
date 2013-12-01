#include "hardpoint.h"

Hardpoint::Hardpoint(glm::vec3 position, Gun *gun){
	m_position = position;
    m_gun = gun;
}

Bullet* Hardpoint::shoot(glm::mat4 shipMatrix, glm::vec3 dir, glm::quat shipOrientation){
    return m_gun->shoot((glm::vec3)(shipMatrix * glm::vec4(m_position, 1.0)), dir, shipOrientation);
}

void Hardpoint::update(float deltasec){
    m_gun->update(deltasec);
}

Gun *Hardpoint::gun(){
    return m_gun;
}