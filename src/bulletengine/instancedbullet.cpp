#include "instancedbullet.h"

#include <glm/gtc/quaternion.hpp>

#include "bulletengine/bulletengine.h"

#include "world/world.h"


InstancedBullet::InstancedBullet(const std::string& name):
    m_name(name),
    m_bufferSlot(-1),
    m_container(nullptr),
    m_dataChanged(true)
{
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
    return m_container;
}

void InstancedBullet::setContainer(InstancedBulletContainer* container) {
    m_container = container;
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
}

void InstancedBullet::setSpeed(const Speed& speed) {
    m_speed = speed;
    updateData();
}

void InstancedBullet::update(float deltaSec) {
    m_transform = m_speed.moved(m_transform, deltaSec);
}

void InstancedBullet::spawn() {
    World::instance()->bulletEngine().add(this);
}

void InstancedBullet::remove() {
    World::instance()->bulletEngine().remove(this);
}

float InstancedBullet::length() {
    return 1.0f; // TODO
}

void InstancedBullet::updateData() {
    m_data.originPosition = m_transform.position();
    m_data.originEulers = glm::eulerAngles(m_transform.orientation());
    m_data.directionalSpeed = m_speed.directional();
    m_data.angularSpeed = m_speed.angular();
    m_data.originTime = World::instance()->time();
    m_data.deathTime = World::instance()->time() + lifetime();
    m_data.active = m_data.originTime < m_data.deathTime;

    m_dataChanged = true;
}

