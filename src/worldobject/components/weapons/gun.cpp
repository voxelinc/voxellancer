#include "gun.h"

#include "world/world.h"
#include "world/god.h"

#include "worldobject/components/hardpoint.h"
#include "worldobject/components/weapons/bulletspawnhelper.h"

#include "bullet.h"


Gun::Gun(const std::string& equipmentKey):
    Weapon(WeaponType::Gun, equipmentKey)
{
}

void Gun::fireAtPoint(const glm::vec3& point) {
    if (canFire()) {
        Bullet *bullet = createBullet();
        bullet->setCreator(hardpoint()->components()->worldObject());

        BulletSpawnHelper bulletSpawnHelper(bullet, hardpoint(), bulletSpeed(), point);
        bulletSpawnHelper.setupBullet();

        World::instance()->god().scheduleSpawn(bullet);

        onFired();
    }
}

void Gun::update(float deltaSec) {
    Weapon::update(deltaSec);
}
