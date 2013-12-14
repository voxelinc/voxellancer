#include "rocket.h"

#include "world/god.h"
#include "world/world.h"

#include "utils/tostring.h"
#include "physics/physics.h"
#include "worldobject/voxelexplosiongenerator.h"


Rocket::Rocket(glm::vec3 position, glm::quat orientation, const glm::vec3& initialSpeed, float travelSpeed, float lifetime, WorldObject* target) :
    WorldObject(0.8f, glm::vec3(0), CollisionFilterClass::Rocket)
{
    m_lifetime = lifetime;
    m_travelSpeed = travelSpeed;
    m_target = target;
    glm::vec3 myOrientation = orientation * glm::vec3(0, 0, -1);

    ClusterCache::instance()->fillObject(this, "data/voxelcluster/rocket.csv");

    m_transform.setOrientation(orientation); //set orientation to ship orientation

    m_transform.setPosition(position + myOrientation * (m_collisionDetector->voxeltree().gridAABB().axisMax(Axis::ZAxis) / 2.0f + 1.4f));

    m_physics->setSpeed(initialSpeed + myOrientation * (m_travelSpeed * 0.1f)); // rocket is ejected with 10% of its travel speed

    m_objectInfo.setName("Rocket");
    m_objectInfo.setShowOnHud(false);
    m_objectInfo.setCanLockOn(false);

    finishInitialization();
}

void Rocket::update(float delta_sec){
    // orient towards target
    if (m_target){
        glm::vec3 dir = glm::inverse(m_transform.orientation()) * glm::normalize(m_target->transform().position() - m_transform.position());
        glm::vec3 myOrientation = glm::vec3(0, 0, -1);
        glm::vec3 cross = glm::cross(dir, myOrientation);
        glm::quat rotation;
        if (cross != glm::vec3(0)){
            glm::vec3 rotationAxis = glm::normalize(cross);
            float angle = glm::acos(glm::dot(dir, myOrientation));
            if (angle > glm::radians(0.1)){
                rotation = glm::angleAxis(-glm::degrees(angle), rotationAxis);
            }
        } else { // the target is either perfectly in front or behind us
            if (dir == -myOrientation)
                rotation = glm::angleAxis(90.0f, glm::vec3(1, 0, 0));
        }

        if (rotation != glm::quat())
            //m_transform.rotate(0.1f * rotation); // directly rotating is easier
            m_physics->setAngularSpeed(0.1f * glm::eulerAngles(rotation));

    }
    // accelerate to travelSpeed
    if (glm::length(m_physics->speed()) < m_travelSpeed){
        float missingSpeed = m_travelSpeed - glm::length(m_physics->speed());
        // accelerate forward, not towards target
        m_physics->accelerate(glm::vec3(0, 0, -missingSpeed));
    }

    m_lifetime -= delta_sec;
    if (m_lifetime < 0)
        World::instance()->god().scheduleRemoval(this);
}

void Rocket::onCollision(){
    World::instance()->god().scheduleRemoval(this);
    VoxelExplosionGenerator generator;
    generator.spawnVoxelExplosion(m_transform.position(), 0xFF0000, m_transform.scale());
}

void Rocket::onSpawnFail(){
    VoxelExplosionGenerator generator;
    generator.spawnVoxelExplosion(m_transform.position(), 0xFF0000, m_transform.scale());
}
