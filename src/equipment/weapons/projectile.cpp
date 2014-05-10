#include "projectile.h"

#include "collision/collisionfilterignoringcreator.h"

#include "sound/soundmanager.h"

#include "voxeleffect/explosion.h"

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

Explosion* Projectile::explosion() {
    return m_explosion.get();
}

void Projectile::setExplosion(const std::shared_ptr<Explosion>& explosion) {
    m_explosion = explosion;
}

void Projectile::update(float deltaSec) {
    WorldObject::update(deltaSec);

    m_lifetime -= deltaSec;

    if (m_lifetime <= 0.0f) {
        World::instance()->god().scheduleRemoval(this);
        onLifetimeOver();
    }
}

void Projectile::onLifetimeOver() {

}

void Projectile::onCollision() {
    SoundManager::current()->play(hitSound(), position());
    if (m_explosion) {
        m_explosion->spawn(transform().position());
    }

    World::instance()->god().scheduleRemoval(this);
}

void Projectile::onSpawnFail() {
    if (m_explosion) {
        m_explosion->spawn(transform().position());
    }
}

