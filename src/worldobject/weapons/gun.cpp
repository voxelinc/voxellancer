#include "gun.h"
#include "world/world.h"
#include "world/god.h"
#include "worldobject/hardpoint.h"
#include "worldobject/ship.h"

Gun::Gun() :
    prop_aimRange("weapons.GunAimRange"),
    prop_cooldownTime("weapons.GunCooldownTime"),
    prop_speed("weapons.GunSpeed"),
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

void Gun::shootAtPoint(Hardpoint* source, glm::vec3 target){
    if (m_cooldown <= 0){
        Bullet *b = new Bullet(Weapon::worldObject(), source->position(), source->ship()->transform().orientation(), target - source->position(), prop_speed, prop_aimRange);
        m_cooldown = prop_cooldownTime;
        World::instance()->god().scheduleSpawn(b);
    }
}

float Gun::aimRange(){
    return prop_aimRange;
}
