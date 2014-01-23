#include "gun.h"
#include "world/world.h"
#include "world/god.h"
#include "worldobject/hardpoint.h"
#include "worldobject/ship.h"
#include "bullettransformhelper.h"


Gun::Gun() :
    m_bulletRange("weapons.GunBulletRange"),
    m_cooldownTime("weapons.GunCooldownTime"),
    m_bulletSpeed("weapons.GunBulletSpeed")
{
    Weapon::setCoolDownTime(m_cooldownTime);
}

AimType Gun::aimType(){
    return Point;
}

void Gun::update(float deltaSec){
    Weapon::update(deltaSec);
}

void Gun::shootAtPoint(Hardpoint* sourceHardpoint, glm::vec3 target) {
    if (canFire()) {
        Bullet *bullet = new Bullet(worldObject(), m_bulletRange / m_bulletSpeed);

        BulletTransformHelper bulletTransformHelper(bullet, sourceHardpoint, m_bulletSpeed, target);
        bulletTransformHelper.transform();

        World::instance()->god().scheduleSpawn(bullet);

        fired();
    }
}

float Gun::range() {
    return m_bulletRange;
}

