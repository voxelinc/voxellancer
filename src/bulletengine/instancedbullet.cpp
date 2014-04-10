#include "instancedbullet.h"

#include <glm/gtc/quaternion.hpp>

#include "equipment/weapons/worldobjectbullet.h"

#include "geometry/line.h"

#include "voxel/voxel.h"
#include "voxel/voxeltree.h"
#include "voxel/voxeltreenode.h"

#include "world/helper/damageimpact.h"
#include "world/world.h"
#include "world/worldlogic.h"

#include "worldtree/worldtree.h"
#include "worldtree/worldtreequery.h"

#include "bulletengine.h"
#include "instancedbulletcontainer.h"


InstancedBullet::InstancedBullet(const Handle<InstancedBulletContainer>& container, const std::string& name):
    m_name(name),
    m_container(container),
    m_bufferSlot(-1),
    m_dataChanged(true),
    m_alive(true),
    m_worldTreeHint(nullptr)
{
    assert(m_container.valid());
    m_lifetime = m_container->prototype().lifetime();

    m_collisionFilter.setCollideableWith(WorldObjectType::Rocket, false);
    m_collisionFilter.setCollideableWith(WorldObjectType::Bullet, false);

    updateData();
    updateCollisionPoint();
}

const std::string& InstancedBullet::name() const {
    return m_name;
}

int InstancedBullet::bufferSlot() const {
    return m_bufferSlot;
}

void InstancedBullet::setBufferSlot(int bufferSlot) {
    m_bufferSlot = bufferSlot;
}

InstancedBulletContainer* InstancedBullet::container() {
    return m_container.get();
}

InstancedBulletData* InstancedBullet::data() {
    return &m_data;
}

bool InstancedBullet::dataChanged() const {
    return m_dataChanged;
}

void InstancedBullet::setDataChanged(bool changed) {
    m_dataChanged = changed;
}

Transform& InstancedBullet::transform() {
    return m_transform;
}

void InstancedBullet::setTransform(const Transform& transform) {
    m_transform = transform;
    updateData();
    updateCollisionPoint();
}

void InstancedBullet::setSpeed(const Speed& speed) {
    m_speed = speed;
    updateData();
}

void InstancedBullet::update(float deltaSec) {
    glm::vec3 collisionLineBegin = m_collisionPoint;
    glm::vec3 collisionLineEnd = m_collisionPoint + m_speed.directional() * deltaSec;

    Line collisionLine(collisionLineBegin, collisionLineEnd);

    WorldTreeQuery query(&World::instance()->worldTree(), &collisionLine, m_worldTreeHint.node(), &m_collisionFilter);
    std::unordered_set<Voxel*> intersectingVoxels = query.intersectingVoxels();

    if (intersectingVoxels.size() > 0) {
        Voxel* voxel = nearestVoxel(intersectingVoxels, collisionLineBegin);
        WorldObject* worldObject = voxel->voxelTreeNode()->voxelTree()->worldObject();
        DamageImpact damageImpact(worldObject, voxel, m_speed.directional(), 5);
        World::instance()->worldLogic().addDamageImpact(damageImpact);
        m_alive = false;
        updateData();
    }

    m_collisionPoint = collisionLineEnd;
    m_transform.setPosition(m_transform.position() + m_speed.directional() * deltaSec);
}

void InstancedBullet::spawn() {
    World::instance()->bulletEngine().add(this);
}

void InstancedBullet::remove() {
    World::instance()->bulletEngine().remove(this);
}

float InstancedBullet::length() {
    assert(m_container.valid());
    return m_container->prototype().length();
}

void InstancedBullet::updateData() {
    m_data.originPosition = m_transform.position();
    m_data.originEulers = glm::eulerAngles(m_transform.orientation());
    m_data.directionalSpeed = m_speed.directional();
    m_data.angularSpeed = m_speed.angular();
    m_data.center = m_container->prototype().transform().center();
    m_data.originTime = World::instance()->time();
    m_data.deathTime = World::instance()->time() + lifetime();
    m_data.active = (m_alive && m_data.originTime < m_data.deathTime) ? 1 : 0;

    m_dataChanged = true;
}

void InstancedBullet::updateCollisionPoint() {
    m_collisionPoint = m_transform.position() + m_transform.orientation() * glm::vec3(0, 0, -length());
}

Voxel* InstancedBullet::nearestVoxel(const std::unordered_set<Voxel*> voxels, const glm::vec3& point) {
    float minDistance = std::numeric_limits<float>::max();
    Voxel* nearestVoxel = nullptr;

    for (Voxel* voxel : voxels) {
        float distance = glm::length(voxel->position() - point);
        if (distance < minDistance) {
            minDistance = distance;
            nearestVoxel = voxel;
        }
    }

    return nearestVoxel;
}

