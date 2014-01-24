#include "bullet.h"

#include "world/god.h"
#include "world/world.h"

#include "utils/tostring.h"
#include "voxeleffect/voxelexplosiongenerator.h"


Bullet::Bullet(WorldObject* creator, float lifetime) :
    WorldObject(0.5f, CollisionFilterClass::Bullet),
    m_creator(creator),
    m_lifetime(lifetime)
{
    ClusterCache::instance()->fillObject(this, "data/voxelcluster/bullet.csv");

    m_objectInfo.setName("Bullet");
    m_objectInfo.setShowOnHud(false);
    m_objectInfo.setCanLockOn(false);

    CollisionFilterable::setCollideableWith(CollisionFilterClass::Bullet, false);

    m_physics.setAngularSpeed(glm::vec3(0.0f, 0.0f, 50));
    m_physics.setDampening(0.0f);
    m_physics.setAngularDampening(0.0f);
}


WorldObject* Bullet::creator() const {
    return m_creator;
}

bool Bullet::specialIsCollideableWith(const CollisionFilterable *other) const {
    return static_cast<CollisionFilterable*>(m_creator) != other;
}

void Bullet::update(float deltaSec) {
    m_lifetime -= deltaSec;

    if (m_lifetime <= 0.0f) {
        World::instance()->god().scheduleRemoval(this);
    }
}

void Bullet::onCollision() {
    World::instance()->god().scheduleRemoval(this);
    spawnExplosion();
}

void Bullet::onSpawnFail() {
    spawnExplosion();
}

void Bullet::spawnExplosion() {
    VoxelExplosionGenerator generator;
    generator.setPosition(m_transform.position());
    generator.setRadius(m_transform.scale());
    generator.setScale(m_transform.scale() / 2.0f);
    generator.setCount(16);
    generator.setColor(0xFF0000, emissiveness());
    generator.setForce(0.6f);
    generator.setLifetime(0.7f, 0.2f);
    generator.spawn();
}

float Bullet::emissiveness() {
    return 0.4f;
}

