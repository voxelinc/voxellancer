#include "bullet.h"

#include "collision/collisionfilter.h"

#include "world/god.h"
#include "world/world.h"


Bullet::Bullet():
    Projectile()
{
    collisionFilter().setCollisionFilterClass(CollisionFilterClass::Bullet);
    collisionFilter().setCollideableWith(CollisionFilterClass::Bullet, false);

    m_objectInfo.setShowOnHud(false);
    m_objectInfo.setCanLockOn(false);

    m_physics.setDampening(Acceleration(glm::vec3(0.0f), glm::vec3(0.0f)));
}

void Bullet::update(float deltaSec) {
    Projectile::update(deltaSec);
}

void Bullet::onCollision() {
    World::instance()->god().scheduleRemoval(this);
    spawnExplosion();
}

void Bullet::onSpawnFail() {
    spawnExplosion();
}

