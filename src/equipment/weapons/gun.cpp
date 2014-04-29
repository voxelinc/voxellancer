#include "gun.h"

#include "utils/geometryhelper.h"
#include "utils/glmext/safenormalize.h"

#include "bullet.h"

#include "equipment/hardpoint.h"

#include "physics/physics.h"

#include "resource/worldelementbuilder.h"

#include "sound/soundmanager.h"

#include "voxel/voxelclusterbounds.h"
#include "voxel/specialvoxels/hardpointvoxel.h"

#include "worldobject/worldobject.h"
#include "worldobject/worldobjectcomponents.h"

#include "world/world.h"
#include "world/god.h"


Gun::Gun(const std::string& equipmentKey):
    Weapon(WeaponType::Gun, equipmentKey),
    m_bulletSpeed(100)
{
}

float Gun::bulletSpeed() const {
    return m_bulletSpeed;
}

void Gun::setBulletSpeed(float bulletSpeed) {
    m_bulletSpeed = bulletSpeed;
}

const SoundProperties& Gun::fireSound() const {
    return m_fireSound;
}

void Gun::setFireSound(const SoundProperties& fireSound) {
    m_fireSound = fireSound;
}

void Gun::fireAtPoint(const glm::vec3& point) {
    if (canFire() && hardpoint()->inFieldOfAim(point)) {
        Bullet *bullet =  WorldElementBuilder(projectileName()).buildBullet();
        setupBullet(bullet, point);

        bullet->spawn();

        SoundManager::current()->play(fireSound(), hardpoint()->voxel()->position());

        onFired();
    }
}

void Gun::update(float deltaSec) {
    Weapon::update(deltaSec);
}

void Gun::setupBullet(Bullet* bullet, const glm::vec3& point) {
    Transform bulletTransform(bullet->transform());

    WorldObject* firingWorldObject = m_hardpoint->components()->worldObject();

    glm::quat worldObjectOrientation = firingWorldObject->transform().orientation();
    glm::vec3 bulletDirection = safeNormalize(point - m_hardpoint->voxel()->position(), glm::vec3(0, 0, -1));
    glm::vec3 hardpointDirection = worldObjectOrientation * glm::vec3(0, 0, -1);
    glm::vec3 bulletUp = glm::cross(bulletDirection, hardpointDirection);

    //bulletTransform.setOrientation(Math::quatFromDir(bulletDirection));
    bulletTransform.setOrientation(m_hardpoint->components()->worldObject()->transform().orientation());

    if (normalizeable(bulletUp)) {
        glm::vec3 rotationAxis = safeNormalize(bulletUp);
        float angle = GeometryHelper::angleBetween(bulletDirection, hardpointDirection);
        glm::quat bulletOrientation = glm::angleAxis(-angle, rotationAxis);
        bulletTransform.rotateWorld(bulletOrientation); //then rotate towards target
    }

    float bulletLength = bullet->length();
    float spawnDistance = glm::root_two<float>() * bullet->transform().scale();
    bulletTransform.setPosition(m_hardpoint->voxel()->position() + bulletDirection * (bulletLength / 2.0f + spawnDistance));

    bullet->setTransform(bulletTransform);

    bullet->setSpeed(Speed(
        bulletDirection * bulletSpeed() /*+ firingWorldObject->physics().speed().directional()*/,
        bulletTransform.orientation() * glm::vec3(0, 0, 5.0f)
    ));

    bullet->setCreator(m_hardpoint->components()->worldObject());
}

