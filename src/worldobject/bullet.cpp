#include "bullet.h"

Bullet::Bullet(glm::vec3 position, glm::vec3 direction, float speed, float range){
	transform().setPosition(position);

	//m_speed = speed;
    //speed = 1;
	m_range = range;
    accelerate((direction - position)*speed);
}


void Bullet::updateSpeed(float delta_sec){
}

void Bullet::update(float delta_sec){
    m_range -= m_speed*delta_sec;
    if (m_range < 0)
        World::instance()->god().scheduleRemoval(this);
}

