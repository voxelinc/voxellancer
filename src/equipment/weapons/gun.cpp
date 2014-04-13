#include "gun.h"

#include "utils/geometryhelper.h"

#include "bullet.h"

#include "equipment/hardpoint.h"

#include "physics/physics.h"

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


Gun::Gun(const std::string& equipmentKey):
    Weapon(WeaponType::Gun, equipmentKey)
{
    bulletPrototype = nullptr;
}

Gun::~Gun() = default;

void Gun::fireAtPoint(const glm::vec3& point) {
    if (canFire() && hardpoint()->inFieldOfAim(point)) {
        Bullet *bullet = createBullet();
        setupBullet(bullet, point);

        World::instance()->god().scheduleSpawn(bullet);

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
    glm::vec3 bulletDirection = glm::normalize(point - m_hardpoint->voxel()->position());
    glm::vec3 hardpointDirection = worldObjectOrientation * glm::vec3(0, 0, -1);
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
        bulletDirection * bulletSpeed() /*+ firingWorldObject->physics().speed().directional()*/,
        bulletTransform.orientation() * glm::vec3(0, 0, 5.0f)
    ));

    bullet->setCreator(m_hardpoint->components()->worldObject());
}

bool Gun::isBulletPathClear(const glm::vec3& point, bool checkFriendlyFire) {
    glm::vec3 direction = glm::normalize(point - m_hardpoint->voxel()->position());
    Capsule capsuleToTarget = Capsule::fromTo(m_hardpoint->voxel()->position() + direction*(bulletLength / 2.0f + spawnDistance), point, bulletMaxWidth/2);
    WorldTreeQuery fireDirectionQuery(&World::instance()->worldTree(), &capsuleToTarget, m_owner->collisionDetector().geode()->containingNode(), nullptr);
    for (WorldObject* object : fireDirectionQuery.intersectingWorldObjects()) {
        if (object == m_hardpoint->components()->worldObject()) {
            return false;
        }
        if (checkFriendlyFire && 
            m_owner->objectType() == WorldObjectType::Ship && 
            object->objectType() == WorldObjectType::Ship &&
            !static_cast<Ship*>(object)->character()->faction().relationTo(static_cast<Ship*>(m_owner)->character()->faction()).isHostile()) {
            return false;
        }
    }
    return true;
}

void Gun::setHardpoint(Hardpoint* hardpoint) {
    Weapon::setHardpoint(hardpoint);
    m_owner = m_hardpoint->components()->worldObject();
}

void Gun::createBulletPrototype() {
    bulletPrototype = createBullet();
    bulletMaxWidth = glm::max(bulletPrototype->bounds().minimalGridAABB().extent(XAxis), bulletPrototype->bounds().minimalGridAABB().extent(YAxis)) * bulletPrototype->transform().scale();
    bulletLength = bulletPrototype->bounds().minimalGridAABB().extent(ZAxis) * bulletPrototype->transform().scale();
    spawnDistance = glm::root_two<float>() * bulletPrototype->transform().scale();
}