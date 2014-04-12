#include "instancedbullet.h"

#include <glm/gtc/quaternion.hpp>

#include "equipment/weapons/worldobjectbullet.h"

#include "collision/collisionfilterignoringcreator.h"

#include "geometry/line.h"
#include "geometry/point.h"

#include "physics/physics.h"

#include "voxel/voxel.h"
#include "voxel/voxeltree.h"
#include "voxel/voxeltreenode.h"

#include "world/helper/damageimpact.h"
#include "world/world.h"
#include "world/worldlogic.h"

#include "worldtree/worldtree.h"
#include "worldtree/worldtreenode.h"
#include "worldtree/worldtreequery.h"

#include "bulletengine.h"
#include "instancedbulletcontainer.h"


InstancedBullet::InstancedBullet(const Handle<InstancedBulletContainer>& container, const std::string& name):
    m_name(name),
    m_container(container),
    m_bufferSlot(-1),
    m_dataChanged(true),
    m_alive(true),
    m_collisionFilter(new CollisionFilter()),
    m_worldTreeHint(nullptr)
{
    assert(m_container.valid());
    m_lifetime = m_container->prototype().lifetime();

    m_collisionFilter->setCollideableWith(WorldObjectType::Rocket, false);
    m_collisionFilter->setCollideableWith(WorldObjectType::Bullet, false);

    updateData();
    updateCollisionPoint();
}

const std::string& InstancedBullet::name() const {
    return m_name;
}

bool InstancedBullet::alive() const {
    return m_alive;
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

float InstancedBullet::emissiveness() const {
    assert(m_container.valid());
    return const_cast<InstancedBulletContainer*>(m_container.get())->prototype().emissiveness();
}

const SoundProperties& InstancedBullet::hitSound() const {
    assert(m_container.valid());
    return const_cast<InstancedBulletContainer*>(m_container.get())->prototype().hitSound();
}

void InstancedBullet::setCreator(WorldObject* creator) {
    Bullet::setCreator(creator);

    m_collisionFilter.reset(new CollisionFilterIgnoringCreator(
        nullptr,
        creator,
        m_collisionFilter->collisionMask()
    ));
}

void InstancedBullet::update(float deltaSec) {
    Bullet::update(deltaSec);

    Line collisionLine(m_collisionPoint, m_collisionPoint + m_speed.directional() * deltaSec);

    WorldTreeQuery query(&World::instance()->worldTree(), &collisionLine, m_worldTreeHint.node(), m_collisionFilter.get());
    std::unordered_set<Voxel*> intersectingVoxels = query.intersectingVoxels();

    if (!intersectingVoxels.empty()) {
        Voxel *voxel = nearestVoxel(intersectingVoxels, m_collisionPoint);

        glm::vec3 collisionPointOffset(m_transform.position() - m_collisionPoint);
        m_transform.setPosition(voxel->position() + collisionPointOffset); // so that the explosion can be spawned at the right place

        applyDamage(voxel);

        m_alive = false;
        updateData();

        onCollision();
    } else {
        if (query.containingNode()) {
            m_worldTreeHint = query.containingNode()->hint();
        }

        m_collisionPoint = collisionLine.b();
        m_transform.setPosition(m_transform.position() + m_speed.directional() * deltaSec);
    }
}

void InstancedBullet::spawn() {
    World::instance()->bulletEngine().add(this);
}

void InstancedBullet::remove() {
    m_alive = false;
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

void InstancedBullet::applyDamage(Voxel* voxel) {
    assert(m_container.valid());

    WorldObject* worldObject = voxel->voxelTreeNode()->voxelTree()->worldObject();
    DamageImpact damageImpact(worldObject, voxel, m_speed.directional() * m_container->prototype().physics().mass(), m_container->prototype().collisionFieldOfDamage());

    World::instance()->worldLogic().addDamageImpact(damageImpact);
}

Voxel* InstancedBullet::nearestVoxel(const std::unordered_set<Voxel*> voxels, const glm::vec3& point) const {
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

