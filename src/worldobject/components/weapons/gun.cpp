#include "gun.h"

#include "sound/sound.h"
#include "sound/soundmanager.h"

#include "world/world.h"
#include "world/god.h"

#include "worldobject/components/hardpoint.h"
#include "worldobject/components/weapons/bulletspawnhelper.h"
#include "worldobject/ship.h"

#include "gunbullet.h"


Gun::Gun():
    m_coolDownTime("gun.general.cooldownTime"),
    m_bulletSpeed("gun.bullet.speed"),
    m_bulletLifetime("gun.bullet.lifetime")
{
}

WeaponAimType Gun::aimType() {
    return WeaponAimType::Point;
}

float Gun::estimatedRange() {
    return m_bulletSpeed * m_bulletLifetime;
}

float Gun::cooldownTime() {
    return m_cooldownTime;
}

void Gun::shootAtPoint(const glm::vec3& point) {
    if (canFire()) {
        GunBullet *bullet = new GunBullet(hardpoint()->components()->worldObject(), m_bulletLifetime * m_bulletSpeed);

        BulletSpawnHelper bulletSpawnHelper(bullet, hardpoint(), m_bulletSpeed, point);
        bulletSpawnHelper.setupBullet();

        World::instance()->god().scheduleSpawn(bullet);

        fired();

        SoundManager::current()->play("data/sound/laser.ogg", sourceHardpoint->position())->setVolume(3);
    }
}

void Gun::update(float deltaSec) {
    Weapon::update(deltaSec);
}

