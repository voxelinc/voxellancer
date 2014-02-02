#include "rocket.h"

#include "world/god.h"
#include "world/world.h"


Rocket::Rocket(float lifetime, WorldObject* targetObject, float scale):
    WorldObject(CollisionFilterClass::Rocket, scale),
    m_lifetime(lifetime),
    m_targetHandle(nullptr)
{
    if(targetObject) {
        m_targetHandle = targetObject->handle();
    }

    m_objectInfo.setShowOnHud(false);
    m_objectInfo.setCanLockOn(false);
}

WorldObject* Rocket::targetObject() {
    return *m_targetHandle;
}

void Rocket::update(float deltaSec) {
    WorldObject::update(deltaSec);
}

void Rocket::onCollision() {
    World::instance()->god().scheduleRemoval(this);
    spawnExplosion();
}

void Rocket::onSpawnFail() {
    spawnExplosion();
}

void Rocket::spawnExplosion() {

}
