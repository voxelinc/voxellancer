#include "gun.h"

#include "sound/sound.h"
#include "sound/soundmanager.h"

#include "voxel/specialvoxels/hardpointvoxel.h"

#include "world/world.h"
#include "world/god.h"

#include "worldobject/components/hardpoint.h"
#include "worldobject/components/weapons/bulletspawnhelper.h"
#include "worldobject/ship.h"

#include "gunbullet.h"


Gun::Gun():
    Weapon("gun"),
    m_cooldownTime("gun.general.cooldownTime"),
    m_bulletSpeed("gun.bullet.speed"),
    m_bulletLifetime("gun.bullet.lifetime")
{
}

WeaponAimType Gun::aimType() const {
    return WeaponAimType::Point;
}

float Gun::bulletLifetime() const {
    return m_bulletLifetime;
}

float Gun::bulletSpeed() const {
    return m_bulletSpeed;
}

float Gun::cooldownTime() const {
    return m_cooldownTime;
}

void Gun::shootAtPoint(const glm::vec3& point) {
    if (canFire()) {
        GunBullet *bullet = new GunBullet(hardpoint()->components()->worldObject(), m_bulletLifetime);

        BulletSpawnHelper bulletSpawnHelper(bullet, hardpoint(), m_bulletSpeed, point);
        bulletSpawnHelper.setupBullet();

        World::instance()->god().scheduleSpawn(bullet);

        fired();

        SoundManager::current()->play("data/sound/laser.ogg", hardpoint()->voxel()->position())->setVolume(3);
    }
}

void Gun::update(float deltaSec) {
    Weapon::update(deltaSec);
}

