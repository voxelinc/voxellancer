#include "rocketlauncher.h"
#include "world/world.h"
#include "world/god.h"
#include "worldobject/hardpoint.h"
#include "worldobject/ship.h"

RocketLauncher::RocketLauncher() :
    m_range("weapons.RocketLauncherRange"),
    m_cooldownTime("weapons.RocketLauncherCooldownTime"),
    m_speed("weapons.RocketLauncherBulletSpeed"),
    m_lifetime("weapons.RocketLauncherLifetime")
{
    Weapon::setCoolDownTime(m_cooldownTime);
}

AimType RocketLauncher::aimType(){
    return Object;
}

void RocketLauncher::update(float deltaSec) {
    Weapon::update(deltaSec);
}


void RocketLauncher::shootAtObject(Hardpoint* source, WorldObject* target){
    if (canFire()) {
        Rocket *r = new Rocket(source->position(), source->ship()->transform().orientation(), source->ship()->physics().speed(), m_speed, m_lifetime, target);
        World::instance()->god().scheduleSpawn(r);

        fired();
    }
}

float RocketLauncher::range(){
    return m_range;
}

