#include "rocket.h"

#include <iostream>

#include "ai/aitask.h"
#include "ai/basictasks/directsuicidetask.h"

#include "collision/collisionfilter.h"
#include "collision/collisionfilterignoringcreator.h"

#include "equipment/engineslot.h"

#include "physics/physics.h"

#include "sound/sound.h"
#include "sound/soundmanager.h"

#include "voxeleffect/voxelexplosiongenerator.h"

#include "worldobject/worldobjectcomponents.h"

#include "world/god.h"
#include "world/world.h"


Rocket::Rocket():
    Projectile(),
    m_boardComputer(this),
    m_aiTask(nullptr)
{
    collisionFilter().setCollideableWith(WorldObjectType::Rocket, false);
}

WorldObjectType Rocket::objectType() const {
    return WorldObjectType::Rocket;
}

Transform& Rocket::transform() {
    return WorldObject::transform();
}

void Rocket::setTransform(const Transform& transform) {
    WorldObject::setTransform(transform);
}

void Rocket::setSpeed(const Speed& speed) {
    physics().setSpeed(speed);
}

void Rocket::setCreator(WorldObject* creator) {
    Projectile::setCreator(creator);

    CollisionFilterIgnoringCreator* newCollisionFilter = new CollisionFilterIgnoringCreator(
        this,
        m_creator,
        collisionFilter().collisionMask()
    );

    setCollisionFilter(newCollisionFilter);
}

WorldObject* Rocket::target() {
    return m_targetHandle.get();
}

void Rocket::setTarget(WorldObject* targetObject) {
    if (targetObject) {
        m_targetHandle = makeHandle(targetObject);
        m_aiTask.reset(new DirectSuicideTask(&m_boardComputer, targetObject));
    } else {
        m_targetHandle = Handle<WorldObject>();
        m_aiTask.reset(nullptr);
    }
}

void Rocket::update(float deltaSec) {
    Projectile::update(deltaSec);
    WorldObject::update(deltaSec);

    if (m_aiTask) {
        m_aiTask->update(deltaSec);
        m_boardComputer.update(deltaSec);
    } else {
        components().setEngineState(EngineState(
                glm::vec3(0, 0, -1),
                glm::vec3(0, 0, 0)
            ));
    }
}

void Rocket::spawn() {
    World::instance()->god().scheduleSpawn(this);
}

void Rocket::remove() {
    World::instance()->god().scheduleRemoval(this);
}

void Rocket::onCollision() {
    Projectile::onCollision();
    WorldObject::onCollision();
}

void Rocket::onSpawnFail() {
    Projectile::onSpawnFail();
    WorldObject::onSpawnFail();
}

void Rocket::spawnExplosion() {
    VoxelExplosionGenerator generator(this);

    generator.setPosition(m_transform.position());
    generator.setScale(m_transform.scale() / 3.0f);
    generator.setColor(0xFF0000);
    generator.setEmissiveness(0.4f);
    generator.setCount(150);
    generator.setLifetime(1.0f, 0.2f);
    generator.setForce(1.5f);

    generator.spawn();
}

void Rocket::onLifetimeOver() {
    spawnExplosion();
}

