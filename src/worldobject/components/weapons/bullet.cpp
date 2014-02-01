#include "bullet.h"

Bullet::Bullet(WorldObject* creator, float lifetime, float scale):
    WorldObject(CollisionFilterClass::Bullet, scale),
    m_creator(creator),
    m_lifetime(lifetime)
{
    CollisionFilterable::setCollideableWith(CollisionFilterClass::Bullet, false);

    m_objectInfo.setShowOnHud(false);
    m_objectInfo.setCanLockOn(false);
}

WorldObject* Bullet::creator() const {
    return m_creator;
}

bool Bullet::specialIsCollideableWith(const CollisionFilterable* other) const {
    return static_cast<CollisionFilterable*>(m_creator) != other;
}

void Bullet:: onCollision() {
    World::instance()->god().scheduleRemoval(this);
    spawnExplosion();
}

void Bullet::onSpawnFail() {
    spawnExplosion();
}

void Bullet::update(float deltaSec) {
    WorldObject::update(deltaSec);

    m_lifetime -= deltaSec;

    if (m_lifetime <= 0.0f) {
        World::instance()->god().scheduleRemoval(this);
    }
}

void Bullet::spawnExplosion() {

}
