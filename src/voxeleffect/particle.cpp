#include "particle.h"

#include <algorithm>


Particle::Particle(const WorldTransform& transform, int color, float emissive, float lifetime):
    m_transform(transform),
    m_color(color),
    m_emissive(emissive),
    m_lifetime(lifetime),
    m_directionalDampening(0.0f),
    m_angularDampening(0.0f),
    m_intersectionCheckCountdown(m_intersectionCheckPeriod),
    m_intersectionCheckPeriod("vfx.particleIntersectionCheckPeriod")
{
}

const WorldTransform& Particle::worldTransform() const {
    return m_transform;
}

void Particle::setWorldTransform(const WorldTransform& transform) {
    m_transform = transform;
}

int Particle::color() const {
    return m_color;
}

float Particle::emissive() const{
    return m_emissive;
}

float Particle::lifetime() const {
    return m_lifetime;
}

bool Particle::isDead() const {
    return m_lifetime == 0.0f;
}

void Particle::setDirectionalSpeed(const glm::vec3& speed, float dampening) {
    m_directionalSpeed = speed;
    m_directionalDampening = dampening;
}

void Particle::setAngularSpeed(const glm::vec3& speed, float dampening) {
    m_angularSpeed = speed;
    m_angularDampening = dampening;
}

bool Particle::intersectionCheckDue() const {
    return m_intersectionCheckCountdown < 0;
}

void Particle::intersectionCheckPerformed() {
    m_intersectionCheckCountdown += m_intersectionCheckPeriod;
}

void Particle::update(float deltaSec) {
    m_directionalSpeed *= 1.0f - (m_directionalDampening * deltaSec);
    m_angularSpeed *= 1.0f - (m_angularDampening * deltaSec);

    m_transform.moveWorld(m_directionalSpeed * deltaSec);
    m_transform.rotate(glm::quat(m_angularSpeed * deltaSec));

    m_lifetime = std::max(m_lifetime - deltaSec, 0.0f);

    m_intersectionCheckCountdown -= deltaSec;
}



