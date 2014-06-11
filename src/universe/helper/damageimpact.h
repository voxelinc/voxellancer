#pragma once

#include <glm/glm.hpp>

#include <glow/ref_ptr.h>


class Voxel;
class WorldObject;

class DamageImpact {
public:
    DamageImpact(WorldObject* worldObject, Voxel* voxel, const glm::vec3& damageVec, float fieldOfDamage);

    WorldObject* worldObject();
    const WorldObject* worldObject() const;

    Voxel* voxel();
    const Voxel* voxel() const;

    glm::vec3 damageVec() const;

    float damage() const;
    void setDamage(float damage);

    float fieldOfDamage() const;

    void add(const DamageImpact& damageImpact);


protected:
    glow::ref_ptr<WorldObject> m_worldObject;
    Voxel* m_voxel;
    glm::vec3 m_direction;
    float m_damage;
    float m_fieldOfDamage;

    void makeUniform();
};

