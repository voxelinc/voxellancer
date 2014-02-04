#include "rocket.h"

#include "world/god.h"
#include "world/world.h"
#include "utils/geometryhelper.h"
#include "physics/physics.h"
#include "voxeleffect/voxelexplosiongenerator.h"
#include "worldobject/ship.h"
#include "resource/clustercache.h"
#include "sound/soundmanager.h"
#include "sound/sound.h"
#include "collision/collisionfilterignoringcreator.h"


Rocket::Rocket(glm::vec3 position, glm::quat orientation, const glm::vec3& initialSpeed, float travelSpeed, float lifetime, WorldObject* creator, WorldObject* target) :
    Ship(new CollisionFilterIgnoringCreator(this, creator, CollisionFilterClass::Rocket)),
    m_target(nullptr),
    m_creator(creator),
    m_lifetime(lifetime),
    m_travelSpeed(travelSpeed)
{
    m_transform.setScale(0.8f);

    m_collisionDamageFOV = std::numeric_limits<float>::max(); // equal damage all around

    if (target) {
        m_target = target->handle();
    }
    glm::vec3 myOrientation = orientation * glm::vec3(0, 0, -1);

    ClusterCache::instance()->fillObject(this, "data/voxelcluster/rocket.csv");

    m_sound = SoundManager::current()->play("data/sound/Missile firing fl.ogg", position);
    m_sound->setVolume(50.0f);

    m_transform.setOrientation(orientation); //set orientation to ship orientation

    //TODO: #300
    m_transform.setPosition(position + myOrientation * (bounds().minimalGridAABB().axisMax(Axis::ZAxis) * m_transform.scale() / 2.0f + glm::root_two<float>()));

    m_physics.setSpeed(initialSpeed + myOrientation * (m_travelSpeed * 0.1f)); // rocket is ejected with 10% of its travel speed

    m_objectInfo.setName("Rocket");
    m_objectInfo.setShowOnHud(false);
    m_objectInfo.setCanLockOn(false);
}

void Rocket::update(float deltaSec) {
    // orient towards target
    if (m_target.valid()){
        glm::vec3 dir = glm::inverse(m_transform.orientation()) * glm::normalize(m_target->transform().position() - m_transform.position());
        glm::vec3 myOrientation = glm::vec3(0, 0, -1);
        glm::vec3 cross = glm::cross(dir, myOrientation);
        glm::quat rotation;
        if (cross != glm::vec3(0)) {
            glm::vec3 rotationAxis = glm::normalize(cross);
            float angle = GeometryHelper::angleBetween(dir, myOrientation);
            if (angle > glm::radians(0.1)) {
                rotation = glm::angleAxis(-angle, rotationAxis);
            }
        } else { // the target is either perfectly in front or behind us
            if (dir == -myOrientation) {
                rotation = glm::angleAxis(glm::half_pi<float>(), glm::vec3(1, 0, 0));
            }
        }

        if (rotation != glm::quat()) {
            //m_transform.rotate(0.1f * rotation); // directly rotating is easier
            m_physics.setAngularSpeed(6.0f * glm::eulerAngles(rotation));
        }
    }
    // accelerate to travelSpeed
    if (glm::length(m_physics.speed()) < m_travelSpeed) {
        float missingSpeed = m_travelSpeed - glm::length(m_physics.speed());
        // accelerate forward, not towards target
        m_physics.accelerate(glm::vec3(0, 0, -missingSpeed));
    }

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
    generator.setColor(0xFF0000);
    generator.setEmissiveness(0.8f);
    generator.setCount(200);
    generator.setLifetime(1.0f, 0.2f);
    generator.setForce(1.2f, 0.4f);
    generator.spawn();

}
