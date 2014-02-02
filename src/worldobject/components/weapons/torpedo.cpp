#include "torpedo.h"

#include "world/god.h"
#include "world/world.h"

#include "voxeleffect/voxelexplosiongenerator.h"

#include "sound/soundmanager.h"
#include "sound/sound.h"


Torpedo::Torpedo(float lifetime, WorldObject* target) :
    Rocket(lifetime, target, 0.8f)
{
    m_sound = SoundManager::current()->play("data/sound/Missile firing fl.ogg", transform().position());
    m_sound->setVolume(50.0f);
//
//    glm::vec3 myOrientation = orientation * glm::vec3(0, 0, -1);
//
//    m_transform.setOrientation(orientation);
//    m_transform.setPosition(position + myOrientation * (minimalGridAABB().axisMax(Axis::ZAxis) * m_transform.scale() / 2.0f + glm::root_two<float>()));

    m_objectInfo.setName("Torpedo");
}

void Torpedo::update(float deltaSec) {
    Rocket::update(deltaSec);
//    // orient towards target
//    if (targetObject) {
//        glm::vec3 dir = glm::inverse(m_transform.orientation()) * glm::normalize(m_target->transform().position() - m_transform.position());
//        glm::vec3 myOrientation = glm::vec3(0, 0, -1);
//        glm::vec3 cross = glm::cross(dir, myOrientation);
//        glm::quat rotation;
//        if (cross != glm::vec3(0)) {
//            glm::vec3 rotationAxis = glm::normalize(cross);
//            float angle = GeometryHelper::angleBetween(dir, myOrientation);
//            if (angle > glm::radians(0.1)) {
//                rotation = glm::angleAxis(-angle, rotationAxis);
//            }
//        } else { // the target is either perfectly in front or behind us
//            if (dir == -myOrientation) {
//                rotation = glm::angleAxis(glm::half_pi<float>(), glm::vec3(1, 0, 0));
//            }
//        }
//
//        if (rotation != glm::quat()) {
//            //m_transform.rotate(0.1f * rotation); // directly rotating is easier
//            m_physics.setAngularSpeed(6.0f * glm::eulerAngles(rotation));
//        }
//    }
//
//    // accelerate to travelSpeed
//    if (glm::length(m_physics.directionalSpeed()) < m_travelSpeed) {
//        float missingSpeed = m_travelSpeed - glm::length(m_physics.directionalSpeed());
//        // accelerate forward, not towards target
//        m_physics.accelerateDirectional(glm::vec3(0, 0, -missingSpeed));
//    }
//
//    m_lifetime -= deltaSec;
//
//    if (m_lifetime < 0){
//        World::instance()->god().scheduleRemoval(this);
//        spawnExplosion();
//    }
//
//    m_sound->setPosition(m_transform.position());
}

void Torpedo::onCollision(){
    m_sound->stop();
}

void Torpedo::spawnExplosion(){
    VoxelExplosionGenerator generator;

    generator.setPosition(m_transform.position());
    generator.setScale(m_transform.scale() / 3.0f);
    generator.setColor(0xFF0000, 0.4f);
    generator.setCount(150);
    generator.setLifetime(1.0f, 0.2f);
    generator.setForce(1.5f);

    generator.spawn();

    SoundManager::current()->play("data/sound/102733__sarge4267__explosion3.ogg", m_transform.position());
}

