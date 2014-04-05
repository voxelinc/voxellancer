#include "worldobjectbullet.h"

#include "collision/collisionfilterignoringcreator.h"

#include "world/world.h"


WorldObjectBullet::WorldObjectBullet() {
    collisionFilter().setCollideableWith(WorldObjectType::Bullet, false);

    m_objectInfo->setShowOnHud(false);
    m_objectInfo->setCanLockOn(false);

    m_physics->setDirectionalDampening(unnamedProperty(0.0f));
    m_physics->setAngularDampening(unnamedProperty(0.0f));
}

Transform& WorldObjectBullet::transform() {
    return WorldObject::transform();
}

void WorldObjectBullet::setTransform(const Transform& transform) {
    WorldObject::setTransform(transform);
}

void WorldObjectBullet::setSpeed(const Speed& speed) {
    physics().setSpeed(speed);
}

void WorldObjectBullet::setCreator(WorldObject* creator) {
    Bullet::setCreator(creator);

    CollisionFilterIgnoringCreator* newCollisionFilter = new CollisionFilterIgnoringCreator(
        this,
        m_creator,
        collisionFilter().collisionMask()
    );

    setCollisionFilter(newCollisionFilter);
}

WorldObjectType WorldObjectBullet::objectType() const {
    return WorldObjectType::Bullet;
}

void WorldObjectBullet::remove() {
    World::instance()->god().scheduleRemoval(this);
}

void WorldObjectBullet::spawn() {
    World::instance()->scheduleSpawn(this);
}

float WorldObjectBullet::length() {
    return bounds().minimalGridAABB().extent(ZAxis) * transform().scale();
}

