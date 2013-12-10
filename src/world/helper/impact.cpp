#include "impact.h"

#include <cassert>


Impact::Impact(WorldObject* worldObject, Voxel* voxel, const glm::vec3& speed, float mass):
    m_worldObject(worldObject),
    m_voxel(voxel),
    m_speed(speed),
    m_mass(mass)
{
    assert(m_voxel);
}

WorldObject* Impact::worldObject() {
    return m_worldObject;
}

const WorldObject* Impact::worldObject() const {
    return m_worldObject;
}

Voxel* Impact::voxel() {
    return m_voxel;
}

const Voxel* Impact::voxel() const {
    return m_voxel;
}

const glm::vec3& Impact::speed() const {
    return m_speed;
}

float Impact::mass() const {
    return m_mass;
}

void Impact::add(const Impact& impact) {
    assert(impact.voxel() == m_voxel);
    assert(impact.worldObject() == m_worldObject);

    m_speed += impact.speed();
    m_mass += impact.mass();
}

