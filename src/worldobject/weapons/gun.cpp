#include "gun.h"
#include "world/world.h"
#include "world/god.h"
#include "worldobject/hardpoint.h"
#include "worldobject/ship.h"
#include "bullettransformhelper.h"
#include "sound/sound.h"
#include "sound/soundmanager.h"


Gun::Gun() :
    m_range("weapons.GunRange"),
    m_cooldownTime("weapons.GunCooldownTime"),
    m_bulletSpeed("weapons.GunBulletSpeed")
{
    Weapon::setCoolDownTime(m_cooldownTime);
}

AimType Gun::aimType() {
    return Point;
}

void Gun::update(float deltaSec) {
    Weapon::update(deltaSec);
}

void Gun::shootAtPoint(Hardpoint* sourceHardpoint, glm::vec3 target) {
    if (canFire()) {
        Bullet *bullet = new Bullet(worldObject(), m_range / m_bulletSpeed);

        BulletTransformHelper bulletTransformHelper(bullet, sourceHardpoint, m_bulletSpeed, target);
        bulletTransformHelper.transform();

        World::instance()->god().scheduleSpawn(bullet);
        SoundManager::current()->play("data/sound/laser.ogg", sourceHardpoint->position())->setVolume(3);
        fired();
    }
}

float Gun::range() {
    return m_range;
}

