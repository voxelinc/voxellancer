#include "rocketlauncher.h"
#include "world/world.h"
#include "world/god.h"
#include "worldobject/hardpoint.h"
#include "worldobject/ship.h"
#include "rocket.h"
#include "physics/physics.h"

RocketLauncher::RocketLauncher() :
    m_range("weapons.RocketLauncherRange"),
    m_cooldownTime("weapons.RocketLauncherCooldownTime"),
    m_speed("weapons.RocketLauncherEjectSpeed")
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
        Rocket *r = new Rocket(source->position(), source->ship()->orientation(), source->ship()->physics().speed(), m_speed, source->ship(), target);
        World::instance()->god().scheduleSpawn(r);

        fired();
    }
}
