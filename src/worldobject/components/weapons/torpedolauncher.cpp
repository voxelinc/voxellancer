#include "torpedolauncher.h"

#include "world/world.h"
#include "world/god.h"

#include "resource/worldobjectfactory.h"

#include "torpedo.h"


TorpedoLauncher::TorpedoLauncher():
    Weapon("torpedolauncher"),
    m_cooldownTime("torpedolauncher.general.cooldownTime"),
    m_torpedoLifetime("torpedolauncher.rocket.lifetime"),
    m_torpedoTravelspeed("torpedolauncher.rocket.travelspeed")
{
}

WeaponAimType TorpedoLauncher::aimType() const {
    return WeaponAimType::Object;
}

float TorpedoLauncher::bulletLifetime() const {
    return m_torpedoLifetime;
}

float TorpedoLauncher::bulletSpeed() const {
    return m_torpedoTravelspeed;
}

float TorpedoLauncher::cooldownTime() const {
    return m_cooldownTime;
}

void TorpedoLauncher::shootAtObject(WorldObject* targetObject) {
    if (canFire()) {
//        Torpedo* torpedo = WorldObjectFactory::build<Rocket>("torpedo");
//
//        World::instance()->god().scheduleSpawn(torpedo);
//        fired();
    }
}

void TorpedoLauncher::update(float deltaSec) {
    Weapon::update(deltaSec);
}

