#include "rocket.h"

#include "world/god.h"
#include "world/world.h"
#include "utils/geometryhelper.h"
#include "physics/physics.h"
#include "voxeleffect/voxelexplosiongenerator.h"
#include "worldobject/ship.h"
#include "ai/character.h" //ship holds a unique_ptr to a character and we inherit from it (C2338)
#include "ai/characters/dummycharacter.h"
#include "ai/basictasks/directsuicidetask.h"
#include "ai/boardcomputer.h"
#include "resource/clustercache.h"
#include "sound/soundmanager.h"
#include "sound/sound.h"


Rocket::Rocket(glm::vec3 position, glm::quat orientation, const glm::vec3& initialSpeed, float ejectSpeed, WorldObject* target) :
    Ship(),
    m_target(nullptr)
{
    m_collisionFilterClass = CollisionFilterClass::Rocket;
    setCollideableWith(CollisionFilterClass::Rocket, false);
    m_transform.setScale(0.5f);

    m_lifetime = Property<float>("rocket.lifetime");;
    prop_maxSpeed = Property<float>("rocket.maxSpeed");
    prop_maxRotSpeed = Property<float>("rocket.maxRotSpeed");
    if (target) {
        m_target = target->handle();
    }
    glm::vec3 myOrientation = orientation * glm::vec3(0, 0, -1);

    ClusterCache::instance()->fillObject(this, "data/voxelcluster/rocket.csv");

    m_sound = SoundManager::current()->play("data/sound/Missile firing fl.ogg", position);
    m_sound->setVolume(50.0f);

    m_transform.setOrientation(orientation); //set orientation to ship orientation

    float halfRocketLength = bounds().minimalGridAABB().axisMax(Axis::ZAxis) * m_transform.scale() / 2.0f;
    m_transform.setPosition(position + myOrientation * (halfRocketLength + glm::root_two<float>()));

    m_physics.setSpeed(initialSpeed + myOrientation * ejectSpeed);

    m_objectInfo.setName("Rocket");
    m_objectInfo.setShowOnHud(false);
    m_objectInfo.setCanLockOn(false);

    m_character.reset(new DummyCharacter(*this, new DirectSuicideTask(*this, target)));
}

void Rocket::update(float deltaSec) {
    m_lifetime -= deltaSec;

    if (m_lifetime < 0){
        World::instance()->god().scheduleRemoval(this);
        spawnExplosion();
    }

    m_sound->setPosition(m_transform.position());

    Ship::update(deltaSec);
}

void Rocket::onCollision(){
    m_sound->stop();
    SoundManager::current()->play("data/sound/102733__sarge4267__explosion3.ogg", m_transform.position());

    World::instance()->god().scheduleRemoval(this);
    spawnExplosion();
}

void Rocket::onSpawnFail(){
    spawnExplosion();
}

void Rocket::spawnExplosion(){
    VoxelExplosionGenerator generator;
    generator.setPosition(m_transform.position());
    generator.setScale(m_transform.scale() / 3.0f);
    generator.setColor(0xFF0000, 0.4f);
    generator.setCount(150);
    generator.setLifetime(1.0f, 0.2f);
    generator.setForce(1.5f);
    generator.spawn();

}
