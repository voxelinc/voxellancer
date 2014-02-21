#include "gun.h"

#include "utils/geometryhelper.h"

#include "sound/sound.h"
#include "sound/soundmanager.h"


#include "world/world.h"
#include "world/god.h"

#include "voxel/specialvoxels/hardpointvoxel.h"
#include "worldobject/worldobjectcomponents.h"
#include "worldobject/components/hardpoint.h"

#include "bullet.h"
#include "physics/physics.h"
#include "voxel/voxelclusterbounds.h"


Gun::Gun(const std::string& equipmentKey):
    Weapon(WeaponType::Gun, equipmentKey)
{
}

void Gun::fireAtPoint(const glm::vec3& point) {
    if (canFire()) {
        Bullet *bullet = createBullet();
        setupBullet(bullet, point);

        World::instance()->god().scheduleSpawn(bullet);
        SoundManager::current()->play("data/sound/laser.ogg", hardpoint()->voxel()->position())->setVolume(3);

        onFired();
    }
}

void Gun::update(float deltaSec) {
    Weapon::update(deltaSec);
}

void Gun::setupBullet(Bullet* bullet, const glm::vec3& point) {
    Transform bulletTransform(bullet->transform());

    glm::quat shipOrientation = m_hardpoint->components()->worldObject()->transform().orientation();
    glm::vec3 bulletDirection = glm::normalize(point - m_hardpoint->voxel()->position());
    glm::vec3 hardpointDirection = shipOrientation * glm::vec3(0, 0, -1);
    glm::vec3 bulletUp = glm::cross(bulletDirection, hardpointDirection);

    //bulletTransform.setOrientation(Math::quatFromDir(bulletDirection));
    bulletTransform.setOrientation(m_hardpoint->components()->worldObject()->transform().orientation());

    if (bulletUp != glm::vec3(0)) {
        glm::vec3 rotationAxis = glm::normalize(bulletUp);
        float angle = GeometryHelper::angleBetween(bulletDirection, hardpointDirection);
        glm::quat bulletOrientation = glm::angleAxis(-angle, rotationAxis);
        bulletTransform.rotateWorld(bulletOrientation); //then rotate towards target
    }
    
    float bulletLength = bullet->bounds().minimalGridAABB().extent(ZAxis) * bullet->transform().scale();
    float spawnDistance = glm::root_two<float>() * bullet->transform().scale();
    bulletTransform.setPosition(m_hardpoint->voxel()->position() + bulletDirection * (bulletLength / 2.0f + spawnDistance));

    bullet->setTransform(bulletTransform);

    bullet->physics().setSpeed(Speed(
        bulletDirection * bulletSpeed(),
        bulletTransform.orientation() * glm::vec3(0, 0, 5.0f)
    ));

    bullet->setCreator(m_hardpoint->components()->worldObject());
}

