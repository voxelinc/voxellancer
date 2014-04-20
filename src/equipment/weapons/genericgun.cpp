#include "genericgun.h"

#include "resource/worldobjectbuilder.h"

#include "genericbullet.h"

#include "equipment/hardpoint.h"

#include "geometry/capsule.h"

#include "worldtree/worldtreequery.h"
#include "worldtree/worldtreegeode.h"

#include "collision/collisiondetector.h"

#include "voxel/specialvoxels/hardpointvoxel.h"
#include "voxel/voxelclusterbounds.h"

#include "world/world.h"

#include "worldobject/worldobjectcomponents.h"
#include "worldobject/ship.h"

#include "ai/character.h"
#include "factions/faction.h"
#include "factions/factionrelation.h"

#include "resource/clustercache.h"


GenericGun::GenericGun(const std::string& name):
    Gun(name),
    m_bulletSpeed(100),
    m_bulletLifetime(100),
    m_cooldownTime(0)
{
}

float GenericGun::bulletLifetime() const {
    return m_bulletLifetime;
}

void GenericGun::setBulletLifetime(float bulletLifetime) {
    m_bulletLifetime = bulletLifetime;
}

float GenericGun::bulletSpeed() const {
    return m_bulletSpeed;
}

void GenericGun::setBulletSpeed(float bulletSpeed) {
    m_bulletSpeed = bulletSpeed;
}

const Visuals& GenericGun::visuals() const {
    return m_visuals;
}

void GenericGun::setVisuals(const Visuals& visuals) {
    m_visuals = visuals;
}

const SoundProperties& GenericGun::fireSound() const {
    return m_fireSound;
}

void GenericGun::setFireSound(const SoundProperties& fireSound) {
    m_fireSound = fireSound;
}

float GenericGun::cooldownTime() const {
    return m_cooldownTime;
}

void GenericGun::setCooldownTime(float cooldownTime) {
    m_cooldownTime = cooldownTime;
}

const std::string& GenericGun::bulletName() const {
    return m_bulletName;
}

void GenericGun::setBulletName(const std::string& bulletName) {
    m_bulletName = bulletName;
    setBulletExtend(bulletName);
}

Bullet* GenericGun::createBullet() {
    return WorldObjectBuilder(m_bulletName).buildBullet();
}

void GenericGun::setBulletExtend(const std::string& bulletName) {
    //ClusterCache* cache = ClusterCache::instance();
    Bullet* bullet = createBullet();

    m_bulletMaxWidth = glm::max(bullet->bounds().minimalGridAABB().extent(XAxis), bullet->bounds().minimalGridAABB().extent(YAxis))* bullet->transform().scale();
    m_bulletLength = bullet->bounds().minimalGridAABB().extent(ZAxis) * bullet->transform().scale();
    m_spawnDistance = glm::root_two<float>() * bullet->transform().scale();

    //m_bulletMaxWidth = glm::max(cache->gridExtend(filename, XAxis), cache->gridExtend(filename, YAxis))* scale;
    //m_bulletLength = cache->gridExtend(filename, ZAxis) * scale;
    //m_spawnDistance = glm::root_two<float>() * scale;
}
