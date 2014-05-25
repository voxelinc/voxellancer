#include "damageimpact.h"

#include <cassert>

#include "worldobject/worldobject.h"


DamageImpact::DamageImpact(WorldObject* worldObject, Voxel* voxel, const glm::vec3& damageVec, float fieldOfDamage):
    m_worldObject(worldObject),
    m_voxel(voxel),
    m_damageVec(damageVec),
    m_fieldOfDamage(fieldOfDamage)
{
    assert(m_worldObject);
    assert(m_voxel);
}

WorldObject* DamageImpact::worldObject() {
    return m_worldObject;
}

const WorldObject* DamageImpact::worldObject() const {
    return m_worldObject;
}

Voxel* DamageImpact::voxel() {
    return m_voxel;
}

const Voxel* DamageImpact::voxel() const {
    return m_voxel;
}

const glm::vec3& DamageImpact::damageVec() const {
    return m_damageVec;
}

float DamageImpact::damage() const {
    return glm::length(m_damageVec);
}

float DamageImpact::fieldOfDamage() const {
    return m_fieldOfDamage;
}

void DamageImpact::add(const DamageImpact& damageImpact) {
    assert(damageImpact.voxel() == m_voxel);
    assert(damageImpact.worldObject() == m_worldObject);

    m_fieldOfDamage = glm::mix(m_fieldOfDamage, damageImpact.fieldOfDamage(), damage() / (damage() + damageImpact.damage()));

    m_damageVec += damageImpact.damageVec();
}

