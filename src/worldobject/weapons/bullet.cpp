#include "bullet.h"

#include "world/god.h"
#include "world/world.h"

#include "utils/tostring.h"
#include "voxeleffect/voxelexplosiongenerator.h"


Bullet::Bullet(WorldObject* creator, glm::vec3 position, glm::quat orientation, glm::vec3 direction, float speed, float range) :
    WorldObject(0.5f, CollisionFilterClass::Bullet),
    m_creator(creator)
{
    assert(std::isfinite(orientation.x) && std::isfinite(orientation.y) && std::isfinite(orientation.z) && std::isfinite(orientation.w));
    m_lifetime = range / speed;
    glm::vec3 dir = glm::normalize(direction);
    glm::vec3 myOrientation = orientation * glm::vec3(0, 0, -1);
    glm::vec3 cross = glm::cross(dir, myOrientation);

    ClusterCache::instance()->fillObject(this, "data/voxelcluster/bullet.csv");

    m_transform.setOrientation(orientation); //set orientation to ship orientation
    if (cross != glm::vec3(0)){
        glm::vec3 rotationAxis = glm::normalize(cross);
        float angle = glm::acos(glm::clamp(glm::dot(dir, myOrientation), 0.0f, 1.0f));
        glm::quat orientation = glm::angleAxis(-angle, rotationAxis);
        m_transform.rotateWorld(orientation); //then rotate towards target
    }

    m_transform.setPosition(position + dir * (minimalGridAABB().axisMax(Axis::ZAxis) / 2.0f + glm::root_two<float>()));

    m_physics.setSpeed(dir * speed);
    m_physics.setAngularSpeed(glm::vec3(0, 0, 50)); //set spinning

    m_objectInfo.setName("Bullet");
    m_objectInfo.setShowOnHud(false);
    m_objectInfo.setCanLockOn(false);

    CollisionFilterable::setCollideableWith(CollisionFilterClass::Bullet, false);

    m_physics.setDampening(0);
    m_physics.setAngularDampening(0);
}


WorldObject* Bullet::creator() const {
    return m_creator;
}

bool Bullet::specialIsCollideableWith(const CollisionFilterable *other) const {
    return static_cast<CollisionFilterable*>(m_creator) != other;
}

void Bullet::update(float deltaSec){
    m_lifetime -= deltaSec;
    if (m_lifetime < 0)
        World::instance()->god().scheduleRemoval(this);
}

void Bullet::onCollision(){
    World::instance()->god().scheduleRemoval(this);
    VoxelExplosionGenerator generator;
    generator.setTransform(m_transform);
    generator.setColor(0xFF0000);
    generator.setForce(0.5f);
    generator.setLifetime(0.7f, 0.2f);
    generator.spawn();
}

void Bullet::onSpawnFail(){
    VoxelExplosionGenerator generator;
    generator.setTransform(m_transform);
    generator.setColor(0xFF0000);
    generator.setForce(0.5f);
    generator.setLifetime(0.7f, 0.2f);
    generator.spawn();
}
