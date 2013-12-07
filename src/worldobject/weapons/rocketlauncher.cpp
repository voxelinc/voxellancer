#include "rocketlauncher.h"
#include "world/world.h"
#include "world/god.h"
#include "worldobject/hardpoint.h"
#include "worldobject/ship.h"

RocketLauncher::RocketLauncher() :
    prop_aimRange("weapons.RocketAimRange"),
    prop_cooldownTime("weapons.RocketCooldownTime"),
    prop_speed("weapons.RocketSpeed"),
    prop_lifetime("weapons.RocketLifetime"),
    m_cooldown(0)
{
}

AimType RocketLauncher::aimType(){
    return Object;
}

void RocketLauncher::update(float delta_sec){
    if (m_cooldown <= 0){ //avoid negative overflow
        m_cooldown = 0;
    }
    else{
        m_cooldown -= delta_sec;
    }
}


void RocketLauncher::shootAtObject(Hardpoint* source, WorldObject* target){
    if (m_cooldown <= 0){
        Rocket *r = new Rocket(source->position(), source->ship()->transform().orientation(), source->ship()->physics().speed(), prop_speed, prop_lifetime, target);
        m_cooldown = prop_cooldownTime;
        World::instance()->god().scheduleSpawn(r);
    }
}

float RocketLauncher::aimRange(){
    return prop_aimRange;
}
