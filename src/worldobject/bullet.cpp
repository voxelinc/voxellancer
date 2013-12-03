#include "bullet.h"

#include "world/god.h"
#include "world/world.h"

#include "utils/tostring.h"


Bullet::Bullet(glm::vec3 position, glm::quat orientation, glm::vec3 direction, float speed, float range) :
    WorldObject(0.8f)
{
    m_range = range / speed;
    glm::vec3 dir = glm::normalize(direction);
    glm::vec3 myOrientation = orientation * glm::vec3(0, 0, -1);
    glm::vec3 rotationAxis = glm::normalize(glm::cross(dir, myOrientation));
    float angle = glm::acos(glm::dot(dir, myOrientation));

    ClusterCache::instance()->fill(this, "data/voxelcluster/bullet.csv");

    m_transform.setOrientation(orientation); //set orientation to ship orientation
    m_transform.rotateWorld(glm::angleAxis(-glm::degrees(angle), rotationAxis)); //then rotate towards target

    m_transform.setPosition(position + dir * (m_collisionDetector.voxeltree().gridAABB().axisMax(Axis::ZAxis) / 2.0f + 1.4f));

    m_physics.setSpeed(dir * speed);
    m_physics.setAngularSpeed(glm::vec3(0, 0, 500)); //set spinning

    m_hudInfo.setName("Bullet");
    m_hudInfo.setShowOnHud(false);

    finishInitialization();
}


void Bullet::updateSpeed(float delta_sec){
}

void Bullet::update(float delta_sec){
    m_range -= delta_sec;
    if (m_range < 0)
        World::instance()->god().scheduleRemoval(this);
}

