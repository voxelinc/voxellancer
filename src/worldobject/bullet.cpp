#include "bullet.h"

Bullet::Bullet(glm::vec3 position, glm::quat orientation, glm::vec3 direction, float speed, float range){
    m_range = range / speed;
    glm::vec3 dir = glm::normalize(direction);
    glm::vec3 myOrientation = orientation * glm::vec3(0, 0, -1);
    glm::vec3 rotationAxis = glm::normalize(glm::cross(dir, myOrientation));
    float angle = glm::acos(glm::dot(dir, myOrientation));

    m_transform.setPosition(position);
    m_transform.setOrientation(orientation); //set orientation to ship orientation
    m_transform.rotateWorld(glm::angleAxis(-glm::degrees(angle), rotationAxis));
    setSpeed(dir*speed);
}


void Bullet::updateSpeed(float delta_sec){
}

void Bullet::update(float delta_sec){
    m_range -= delta_sec;
    if (m_range < 0)
        World::instance()->god().scheduleRemoval(this);
}

