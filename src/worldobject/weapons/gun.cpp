#include "gun.h"
#include "world/world.h"
#include "world/god.h"

Gun::Gun() :
    prop_aimRange("weapons.GunAimRange"),
    prop_cooldownTime("weapons.GunCooldownTime"),
    prop_bulletSpeed("weapons.GunBulletSpeed"),
    m_cooldown(0)
{
}

AimType Gun::aimType(){
    return Point;
}

void Gun::update(float delta_sec){
    m_cooldown -= delta_sec;
    if (m_cooldown <= 0){ //avoid negative overflow
        m_cooldown = 0;
    }
}


void Gun::shootAtPoint(glm::vec3 position, glm::quat orientation, glm::vec3 target){
    if (m_cooldown <= 0){
        Bullet *b = new Bullet(position, orientation, target - position, prop_bulletSpeed, prop_aimRange);
        m_cooldown = prop_cooldownTime;
        World::instance()->god().scheduleSpawn(b);
    }
}

float Gun::aimRange(){
    return prop_aimRange;
}