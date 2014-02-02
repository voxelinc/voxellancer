#include "torpedolauncher.h"

#include "world/world.h"
#include "world/god.h"

#include "torpedo.h"


TorpedoLauncher::TorpedoLauncher():
    Weapon("torpedolauncher"),
    m_cooldownTime("rocketlauncher.general.cooldownTime"),
    m_torpedoLifetime("rocketlauncher.torpedo.lifetime"),
    m_torpedoTravelspeed("rocketlauncher.torpedo.travelspeed")
{
}

WeaponAimType TorpedoLauncher::aimType() const {
    return WeaponAimType::Object;
}

float TorpedoLauncher::estimatedRange() const {
    return m_torpedoLifetime * m_torpedoTravelspeed;
}

float TorpedoLauncher::cooldownTime() const {
    return m_cooldownTime;
}

void TorpedoLauncher::shootAtObject(WorldObject* targetObject) {
    if (canFire()) {
//        Torpedo* torpedo  = new Torpedo(source->position(), source->ship()->transform().orientation(), source->ship()->physics().directionalSpeed(), m_speed, m_lifetime, target);
//        World::instance()->god().scheduleSpawn(r);
        fired();
    }
}

void TorpedoLauncher::update(float deltaSec) {
    Weapon::update(deltaSec);
}

