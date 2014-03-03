#include "projectile.h"

#include "collision/collisionfilterignoringcreator.h"

#include "world/god.h"
#include "world/world.h"
#include "sound/soundmanager.h"


Projectile::Projectile():
    m_creator(nullptr),
    m_lifetime(0.0f)
{
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

    World::instance()->god().scheduleRemoval(this);
    spawnExplosion();
}

void Projectile::onSpawnFail() {
    spawnExplosion();
}
