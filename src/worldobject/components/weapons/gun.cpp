#include "gun.h"

#include "utils/geometryhelper.h"

#include "voxel/specialvoxels/hardpointvoxel.h"

#include "world/world.h"
#include "world/god.h"

#include "worldobject/components/hardpoint.h"

#include "bullet.h"


Gun::Gun(const std::string& equipmentKey):
    Weapon(WeaponType::Gun, equipmentKey)
{
}

void Gun::fireAtPoint(const glm::vec3& point) {
    if (canFire()) {
        Bullet *bullet = createBullet();
        setupBullet(bullet, point);

        World::instance()->god().scheduleSpawn(bullet);

        onFired();
    }
}

void Gun::update(float deltaSec) {
    Weapon::update(deltaSec);
}

void Gun::setupBullet(Bullet* bullet, const glm::vec3& point) {
    Transform bulletTransform(bullet->transform());

    glm::quat shipOrientation = hardpoint()->components()->worldObject()->transform().orientation();
    glm::vec3 bulletDirection = glm::normalize(point - hardpoint()->voxel()->position());
    glm::vec3 hardpointDirection = shipOrientation * glm::vec3(0, 0, -1);
    glm::vec3 bulletUp = glm::cross(bulletDirection, hardpointDirection);

    //bulletTransform.setOrientation(Math::quatFromDir(bulletDirection));
    bulletTransform.setOrientation(hardpoint()->components()->worldObject()->transform().orientation());

    if (bulletUp != glm::vec3(0)) {
        glm::vec3 rotationAxis = glm::normalize(bulletUp);
        float angle = GeometryHelper::angleBetween(bulletDirection, hardpointDirection);
        glm::quat bulletOrientation = glm::angleAxis(-angle, rotationAxis);
        bulletTransform.rotateWorld(bulletOrientation); //then rotate towards target
    }

    //TODO: #300
    float bulletLength = bullet->bounds().minimalGridAABB().extent(ZAxis) * bullet->transform().scale();
    float spawnDistance = glm::root_two<float>() * bullet->transform().scale();
    bulletTransform.setPosition(hardpoint()->voxel()->position() + bulletDirection * (bulletLength / 2.0f + spawnDistance));

    bullet->setTransform(bulletTransform);

    bullet->physics().setSpeed(Speed(
        bulletDirection * bulletSpeed(),
        bulletTransform.orientation() * glm::vec3(0, 0, 5.0f)
    ));

    bullet->setCreator(hardpoint()->components()->worldObject());
}
