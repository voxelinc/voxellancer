#include "rocket.h"

#include <iostream>

#include "collision/collisionfilter.h"

#include "world/god.h"
#include "world/world.h"


Rocket::Rocket():
    Projectile(),
    m_targetHandle(nullptr)
{
    collisionFilter().setCollisionFilterClass(CollisionFilterClass::Rocket);

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

    components().setEngineState(EngineState(
        glm::vec3(0, 0, -1),
        glm::vec3(0, 0, 0)
    ));

    // TODO: follow target
}

void Rocket::onCollision() {
    World::instance()->god().scheduleRemoval(this);
    spawnExplosion();
}

void Rocket::onSpawnFail() {
    spawnExplosion();
}


