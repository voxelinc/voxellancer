#include "bullet.h"

#include "world/god.h"
#include "world/world.h"

#include "utils/tostring.h"
#include "physics/bulletphysics.h"


Bullet::Bullet(WorldObject* creator, glm::vec3 position, glm::quat orientation, glm::vec3 direction, float speed, float range) :
    WorldObject(CollisionFilterClass::Bullet, new BulletPhysics(*this), new CollisionDetector(*this), 0.5f),
    m_creator(creator)
{
    m_lifetime = range / speed;
    glm::vec3 dir = glm::normalize(direction);
    glm::vec3 myOrientation = orientation * glm::vec3(0, 0, -1);
    glm::vec3 cross = glm::cross(dir, myOrientation);

    ClusterCache::instance()->fillObject(this, "data/voxelcluster/bullet.csv");

    m_transform.setOrientation(orientation); //set orientation to ship orientation
    if (cross != glm::vec3(0)){
        glm::vec3 rotationAxis = glm::normalize(cross);
        float angle = glm::acos(glm::dot(dir, myOrientation));
        m_transform.rotateWorld(glm::angleAxis(-glm::degrees(angle), rotationAxis)); //then rotate towards target
    }

    m_transform.setPosition(position + dir * (m_collisionDetector->voxeltree().gridAABB().axisMax(Axis::ZAxis) / 2.0f + 1.4f));

    m_physics->setSpeed(dir * speed);
    m_physics->setAngularSpeed(glm::vec3(0, 0, 50)); //set spinning

    m_objectInfo.setName("Bullet");
    m_objectInfo.setShowOnHud(false);
    m_objectInfo.setCanLockOn(false);

    CollisionFilterable::setCollideableWith(CollisionFilterClass::Bullet, false);

    finishInitialization();
}

WorldObject* Bullet::creator() const {
    return m_creator;
}

bool Bullet::isCollideableWith(const CollisionFilterable *other) const {
    if(m_creator == other) {
        return false;
    }

    return WorldObject::isCollideableWith(other);
}

void Bullet::update(float delta_sec){
    m_lifetime -= delta_sec;
    if (m_lifetime < 0)
        World::instance()->god().scheduleRemoval(this);
}

void Bullet::onImpact(){
    //TODO: spawn explosion
    World::instance()->god().scheduleRemoval(this);
}

void Bullet::onSpawnFail(){
    //TODO: spawn explosion
}
