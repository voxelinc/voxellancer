#include "bullet.h"

#include "world/god.h"
#include "world/world.h"
#include "utils/geometryhelper.h"
#include "voxeleffect/voxelexplosiongenerator.h"
#include "resource/clustercache.h"
#include "sound/sound.h"
#include "sound/soundmanager.h"
#include "collision/collisionfilterignoringcreator.h"


Bullet::Bullet(WorldObject* creator, float lifetime) :
    WorldObject(new CollisionFilterIgnoringCreator(this, creator, CollisionFilterClass::Bullet), 0.5f),
    m_lifetime(lifetime)
{
    ClusterCache::instance()->fillObject(this, "data/voxelcluster/bullet.csv");

    m_collisionFieldOfDamage = glm::pi<float>() * 2;

    m_objectInfo.setName("Bullet");
    m_objectInfo.setShowOnHud(false);
    m_objectInfo.setCanLockOn(false);

    m_collisionFilter->setCollideableWith(CollisionFilterClass::Bullet, false);

    m_physics.setAngularSpeed(glm::vec3(0.0f, 0.0f, 50));
    m_physics.setDampening(0.0f);
    m_physics.setAngularDampening(0.0f);
}

void Bullet::update(float deltaSec) {
    m_lifetime -= deltaSec;

    if (m_lifetime <= 0.0f) {
        World::instance()->god().scheduleRemoval(this);
    }
}

void Bullet::onCollision() {
    SoundManager::current()->play("data/sound/hit2.ogg", m_transform.position());
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
    generator.setColor(0xFF0000);
    generator.setEmissiveness(emissiveness());
    generator.setForce(0.6f, 0.2f);
    generator.setLifetime(0.5f, 0.2f);
    generator.spawn();
}

float Bullet::emissiveness() {
    return 0.8f;
}

