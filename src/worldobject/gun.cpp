#include "gun.h"
#include "world/world.h"
#include "world/god.h"

Gun::Gun(float speed, float range, float cooldown){
    m_speed = speed;
    m_range = range;
    m_cooldownTime = cooldown;
    m_cooldown = 0;
}

AimType Gun::aimType(){
    return Point;
}

void Gun::update(float delta_sec){
    if (m_cooldown <= 0){ //avoid negative overflow
        m_cooldown = 0;
    }
    else{
        m_cooldown -= delta_sec;
    }
}


void Gun::shootAtPoint(glm::vec3 position, glm::quat orientation, glm::vec3 target){
    if (m_cooldown <= 0){
        Bullet *b = new Bullet(position, orientation, target - position, m_speed, m_range);
        m_cooldown = m_cooldownTime;
        World::instance()->god().scheduleSpawn(b);
    }
}

float Gun::range(){
    return m_range;
}
