#include "projectile.h"

#include "collision/collisionfilterignoringcreator.h"

#include "sound/soundmanager.h"

#include "world/god.h"
#include "world/world.h"

#include "worldobject/worldobjectinfo.h"


Projectile::Projectile():
    m_creator(nullptr),
    m_lifetime(0.0f)
{
    m_info->setShowOnHud(false);
    m_info->setCanLockOn(false);
}

WorldObject* Projectile::creator() {
    return m_creator;
}

void Projectile::setCreator(WorldObject* creator) {
    m_creator = creator;

    CollisionFilterIgnoringCreator* newCollisionFilter = new CollisionFilterIgnoringCreator(
        this,
        m_creator,
        collisionFilter().collisionMask()
    );

    setCollisionFilter(newCollisionFilter);
}

float Projectile::lifetime() const {
    return m_lifetime;
}

void Projectile::setLifetime(float lifetime) {
    m_lifetime = lifetime;
}

const SoundProperties& Projectile::hitSound() const {
    return m_hitSound;
}

void Projectile::setHitSound(const SoundProperties& hitSound) {
    m_hitSound = hitSound;
}

void Projectile::update(float deltaSec) {
    WorldObject::update(deltaSec);

    m_lifetime -= deltaSec;

    if (m_lifetime <= 0.0f) {
        scheduleRemoval();
        onLifetimeOver();
    }
}

void Projectile::onLifetimeOver() {

}

void Projectile::onCollision() {
    SoundManager::current()->play(hitSound(), position());

    scheduleRemoval();
    spawnExplosion();
}

void Projectile::onSpawnFail() {
    spawnExplosion();
}

