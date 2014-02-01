#include "rocket.h"

Rocket::Rocket(float lifetime, WorldObject* targetObject, float scale):
    WorldObject(CollisionFilterableClass::Rocket, scale),
    m_lifetime(lifetime)
{
    if(targetObject) {
        m_targetHandle = targetObject->handle();
    }

    m_objectInfo.setShowOnHud(false);
    m_objectInfo.setCanLockOn(false);
}

WorldObject* targetObject() {
    return m_targetHandle;
}

void Rocket::update(float deltaSec) {
    Worldobject::update();
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
