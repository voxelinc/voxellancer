#include "voxelparticle.h"

#include <algorithm>


VoxelParticle::VoxelParticle(const WorldTransform& transform, int color, float lifetime):
    m_transform(transform),
    m_color(color),
    m_lifetime(lifetime),
    m_directionalDampening(0.0f),
    m_angularDampening(0.0f)
{
    m_colorVec.x = (m_color >> 16) / 255.0f;
    m_colorVec.y = ((m_color & 0xFF00) >> 8) / 255.0f;
    m_colorVec.z = (m_color & 0xFF) / 255.0f;
}

const WorldTransform& VoxelParticle::worldTransform() const {
    return m_transform;
}

void VoxelParticle::setWorldTransform(const WorldTransform& transform) {
    m_transform = transform;
}

int VoxelParticle::color() const {
    return m_color;
}

const glm::vec3& VoxelParticle::colorVec() const {
    return m_colorVec;
}

float VoxelParticle::lifetime() const {
    return m_lifetime;
}

bool VoxelParticle::isDead() const {
    return m_lifetime == 0.0f;
}

void VoxelParticle::setDirectionalSpeed(const glm::vec3& speed, float dampening) {
    m_directionalSpeed = speed;
    m_directionalDampening = dampening;
}

void VoxelParticle::setAngularSpeed(const glm::vec3& speed, float dampening) {
    m_angularSpeed = speed;
    m_angularDampening = dampening;
}

void VoxelParticle::update(float deltaSec) {
    m_directionalSpeed *= 1.0f - (m_directionalDampening * deltaSec);
    m_angularSpeed *= 1.0f - (m_angularDampening * deltaSec);

    m_transform.moveWorld(m_directionalSpeed * deltaSec);
    m_transform.rotate(glm::quat(m_angularSpeed * deltaSec));

    m_lifetime = std::max(m_lifetime - deltaSec, 0.0f);
}

