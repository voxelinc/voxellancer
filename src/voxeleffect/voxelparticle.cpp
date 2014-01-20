#include "voxelparticle.h"

#include <algorithm>


Property<float>* VoxelParticle::s_intersectionCheckPeriod = nullptr;



VoxelParticle::VoxelParticle(const WorldTransform& transform, int color, float emissiveness, float lifetime):
    m_transform(transform),
    m_color(color),
    m_emissiveness(emissiveness),
    m_lifetime(lifetime),
    m_directionalDampening(0.0f),
    m_angularDampening(0.0f)
{
    if (s_intersectionCheckPeriod == nullptr) {
        s_intersectionCheckPeriod = new Property<float>("vfx.particleIntersectionCheckPeriod");
    }
    m_intersectionCheckCountdown = s_intersectionCheckPeriod->get();
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

float VoxelParticle::emissiveness() const{
    return m_emissiveness;
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

bool VoxelParticle::intersectionCheckDue() const {
    return m_intersectionCheckCountdown < 0;
}

void VoxelParticle::intersectionCheckPerformed() {
    m_intersectionCheckCountdown = s_intersectionCheckPeriod->get();
}

void VoxelParticle::update(float deltaSec) {
    m_directionalSpeed *= 1.0f - (m_directionalDampening * deltaSec);
    m_angularSpeed *= 1.0f - (m_angularDampening * deltaSec);

    m_transform.moveWorld(m_directionalSpeed * deltaSec);
    m_transform.rotate(glm::quat(m_angularSpeed * deltaSec));

    m_lifetime = std::max(m_lifetime - deltaSec, 0.0f);

    m_intersectionCheckCountdown -= deltaSec;
}



