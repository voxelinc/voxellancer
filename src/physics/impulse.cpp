#include "impulse.h"

#include <cassert>


Impulse::Impulse(WorldObject* worldObject, Voxel* voxel, const glm::vec3& speed, float mass, const glm::vec3& normal):
    m_worldObject(worldObject),
    m_voxel(voxel),
    m_speed(speed),
    m_mass(mass),
    m_normal(glm::normalize(normal))
{
    assert(m_voxel);
}

WorldObject* Impulse::worldObject() {
    return m_worldObject;
}

const WorldObject* Impulse::worldObject() const {
    return m_worldObject;
}

Voxel* Impulse::voxel() {
    return m_voxel;
}

const Voxel* Impulse::voxel() const {
    return m_voxel;
}

const glm::vec3& Impulse::speed() const {
    return m_speed;
}

float Impulse::mass() const {
    return m_mass;
}

const glm::vec3& Impulse::normal() const {
    return m_normal;
}

void Impulse::add(const Impulse& impulse) {
    assert(impulse.voxel() == m_voxel);
    assert(impulse.worldObject() == m_worldObject);

    m_speed += impulse.speed();
    m_mass += impulse.mass();
}

