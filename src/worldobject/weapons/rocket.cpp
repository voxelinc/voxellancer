#include "rocket.h"

#include "world/god.h"
#include "world/world.h"

#include "utils/tostring.h"
#include "physics/physics.h"


Rocket::Rocket(glm::vec3 position, glm::quat orientation, const glm::vec3& initialSpeed, float travelSpeed, float lifetime, WorldObject* target) :
    WorldObject(0.8f)
{
    m_lifetime = lifetime;
    m_travelSpeed = travelSpeed;
    glm::vec3 myOrientation = orientation * glm::vec3(0, 0, -1);

        ClusterCache::instance()->fillObject(this, "data/voxelcluster/rocket.csv");

        m_transform.setOrientation(orientation); //set orientation to ship orientation


    m_transform.setPosition(position + myOrientation * (m_collisionDetector->voxeltree().gridAABB().axisMax(Axis::ZAxis) / 2.0f + 1.4f));

    m_physics->setSpeed(initialSpeed);

    m_objectInfo.setName("Rocket");
    m_objectInfo.setShowOnHud(false);
    m_objectInfo.setCanLockOn(false);

    finishInitialization();
}

void Rocket::update(float delta_sec){
    // orient towards target
    

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

