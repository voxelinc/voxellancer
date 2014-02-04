#pragma once

#include <glm/glm.hpp>


class Voxel;
class WorldObject;

class DamageImpact
{
public:
    DamageImpact(WorldObject* worldObject, Voxel* voxel, const glm::vec3& damageVec, float damageFOV);

    WorldObject* worldObject();
    const WorldObject* worldObject() const;

    Voxel* voxel();
    const Voxel* voxel() const;

    const glm::vec3& damageVec() const;

    float damage() const;

    float damageFOV() const;

    void add(const DamageImpact& damageImpact);


protected:
    WorldObject* m_worldObject;
    Voxel* m_voxel;
    glm::vec3 m_damageVec;
    float m_damageFOV;
};

