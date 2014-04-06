#include "damageimpact.h"

#include <cassert>


DamageImpact::DamageImpact(WorldObject* worldObject, Voxel* voxel, const glm::vec3& damageVec, float fieldOfDamage):
    m_worldObject(worldObject),
    m_voxel(voxel),
    m_fieldOfDamage(fieldOfDamage)
{
    assert(m_worldObject);
    assert(m_voxel);

    if (glm::length(damageVec) > 0) {
        m_direction = glm::normalize(damageVec);
        m_damage = glm::length(damageVec);
    } else {
        makeUniform();
        m_damage = 0.0f;
    }
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

glm::vec3 DamageImpact::damageVec() const {
    return m_direction * m_damage;
}

float DamageImpact::damage() const {
    return m_damage;
}

void DamageImpact::setDamage(float damage) {
    m_damage = damage;
}

float DamageImpact::fieldOfDamage() const {
    return m_fieldOfDamage;
}

void DamageImpact::add(const DamageImpact& damageImpact) {
    assert(damageImpact.voxel() == m_voxel);
    assert(damageImpact.worldObject() == m_worldObject);

    m_fieldOfDamage = glm::mix(m_fieldOfDamage, damageImpact.fieldOfDamage(), damage() / (damage() + damageImpact.damage()));

    glm::vec3 damageVecSum = damageVec() + damageImpact.damageVec();

    if (glm::length(damageVecSum) == 0) { // This is extremely unlikely to happen
        makeUniform();
    } else {
        m_direction = glm::normalize(damageVecSum);
    }

    m_damage += damageImpact.damage();
}

void DamageImpact::makeUniform() {
    m_direction = glm::vec3(1.0f, 0.0f, 0.0f);
    m_fieldOfDamage = std::numeric_limits<float>::infinity();
}

