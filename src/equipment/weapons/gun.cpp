#include "gun.h"

#include "utils/geometryhelper.h"
#include "utils/safenormalize.h"

#include "bullet.h"

#include "equipment/hardpoint.h"

#include "physics/physics.h"

#include "resource/worldobjectbuilder.h"

#include "sound/soundmanager.h"

#include "voxel/voxelclusterbounds.h"
#include "voxel/specialvoxels/hardpointvoxel.h"

#include "worldobject/worldobjectcomponents.h"
#include "worldobject/ship.h"

#include "collision/collisiondetector.h"

#include "geometry/capsule.h"

#include "factions/faction.h"
#include "factions/factionmatrix.h"
#include "factions/factionrelation.h"

#include "ai/character.h"

#include "worldtree/worldtreequery.h"
#include "worldtree/worldtreegeode.h"

#include "world/world.h"
#include "world/god.h"

#include "resource/clustercache.h"


Gun::Gun(const std::string& equipmentKey):
    Weapon(WeaponType::Gun, equipmentKey),
    m_bulletSpeed(100)
{
}

Gun::~Gun() = default;

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

void Gun::fireAtPoint(const glm::vec3& point, bool checkFriendlyFire) {
    if (!canFire()) {
        return;
    }

    if (!m_hardpoint->inFieldOfAim(point)) {
        return;
    }

    if (!isBulletPathClear(point, checkFriendlyFire)) {
        return;
    }

    Bullet *bullet =  WorldObjectBuilder(projectileName()).buildBullet();
    setupBullet(bullet, point);

    World::instance()->god().scheduleSpawn(bullet);

    SoundManager::current()->play(fireSound(), hardpoint()->voxel()->position());

    onFired();
}

bool Gun::isBulletPathClear(const glm::vec3& point, bool checkFriendlyFire) {
    WorldObject* owner = m_hardpoint->components()->worldObject();

    glm::vec3 direction = glm::normalize(point - m_hardpoint->voxel()->position());
    Capsule capsuleToTarget = Capsule::fromTo(m_hardpoint->voxel()->position() + direction * (m_bulletLength / 2.0f + m_spawnDistance), point, m_bulletMaxWidth / 2);

    WorldTreeQuery fireDirectionQuery(&World::instance()->worldTree(), &capsuleToTarget, owner->collisionDetector().geode()->hint(), nullptr);

    Faction* ownerFaction = owner->objectType() == WorldObjectType::Ship ?
                                static_cast<Ship*>(owner)->character()->faction() :
                                nullptr;

    for (WorldObject* object : fireDirectionQuery.intersectingWorldObjects()) {
        if (object == m_hardpoint->components()->worldObject()) {
            return false;
        }

        Faction* objectFaction = object->objectType() == WorldObjectType::Ship ?
                                    static_cast<Ship*>(owner)->character()->faction():
                                    nullptr;

        if (checkFriendlyFire) {
            if (ownerFaction && objectFaction) {
                if (ownerFaction->relationTo(*objectFaction).isFriendly()) {
                    return false;
                }
            }
        }
    }
    return true;
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

    bulletTransform.setOrientation(m_hardpoint->components()->worldObject()->transform().orientation());

    if (normalizeable(bulletUp)) {
        glm::vec3 rotationAxis = glm::normalize(bulletUp);
        float angle = GeometryHelper::angleBetween(bulletDirection, hardpointDirection);
        glm::quat bulletOrientation = glm::angleAxis(-angle, rotationAxis);
        bulletTransform.rotateWorld(bulletOrientation); //then rotate towards target
    }

    m_spawnDistance = glm::root_two<float>() * bullet->transform().scale();
    bulletTransform.setPosition(m_hardpoint->voxel()->position() + bulletDirection * (m_bulletLength / 2.0f + m_spawnDistance));

    bullet->setTransform(bulletTransform);

    bullet->physics().setSpeed(Speed(
        bulletDirection * bulletSpeed() /*+ firingWorldObject->physics().speed().directional()*/,
        bulletTransform.orientation() * glm::vec3(0, 0, 5.0f)
    ));

    bullet->setCreator(m_hardpoint->components()->worldObject());
}

void Gun::setBulletExtend() {
    Bullet* bullet = WorldObjectBuilder(projectileName()).buildBullet();

    m_bulletMaxWidth = glm::max(bullet->bounds().minimalGridAABB().extent(XAxis), bullet->bounds().minimalGridAABB().extent(YAxis))* bullet->transform().scale();
    m_bulletLength = bullet->bounds().minimalGridAABB().extent(ZAxis) * bullet->transform().scale();
    m_spawnDistance = glm::root_two<float>() * bullet->transform().scale();
    m_bulletLifetime = bullet->lifetime();

    delete bullet;
}

void Gun::onProjectileNameChanged() {
    setBulletExtend();
}

float Gun::bulletLifetime() const {
    return m_bulletLifetime;
}
