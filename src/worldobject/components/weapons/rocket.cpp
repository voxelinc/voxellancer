#include "rocket.h"

#include "collision/collisionfilter.h"

#include "world/god.h"
#include "world/world.h"


Rocket::Rocket():
    Projectile(),
    m_targetHandle(nullptr)
{
    collisionFilter().setCollisionFilterClass(CollisionFilterClass::Rocket);
    collisionFilter().setCollideableWith(CollisionFilterClass::Rocket, false);

    m_objectInfo.setShowOnHud(false);
    m_objectInfo.setCanLockOn(false);
}

WorldObject* Rocket::target() {
    return m_targetHandle.get();
}

void Rocket::setTarget(WorldObject* targetObject) {
    m_targetHandle = targetObject->handle();
}

void Rocket::update(float deltaSec) {
    Projectile::update(deltaSec);
    // TODO: follow target
}

void Rocket::onCollision() {
    World::instance()->god().scheduleRemoval(this);
    spawnExplosion();
}

void Rocket::onSpawnFail() {
    spawnExplosion();
}


