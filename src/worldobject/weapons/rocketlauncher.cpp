#include "rocketlauncher.h"
#include "world/world.h"
#include "world/god.h"
#include "worldobject/hardpoint.h"
#include "worldobject/ship.h"
#include "rocket.h"

RocketLauncher::RocketLauncher() :
    m_range("weapons.RocketLauncherRange"),
    m_cooldownTime("weapons.RocketLauncherCooldownTime"),
    m_speed("weapons.RocketLauncherSpeed"),
    m_lifetime("weapons.RocketLauncherLifetime")
{
    setCoolDownTime(m_cooldownTime);
}

AimType RocketLauncher::aimType() {
    return AimType::Object;
}

float RocketLauncher::bulletSpeed() const {
    return m_speed;
}

float RocketLauncher::range() {
    return m_range;
}

void RocketLauncher::update(float deltaSec) {
    Weapon::update(deltaSec);
}

void RocketLauncher::shootAtObject(Hardpoint* source, WorldObject* target){
    if (canFire()) {
        Rocket *r = new Rocket(source->position(), source->ship()->transform().orientation(), source->ship()->physics().speed(), m_speed, m_lifetime, source->ship(), target);
        World::instance()->god().scheduleSpawn(r);

        fired();
    }
}
