#pragma once

#include <glm/glm.hpp>


class Voxel;
class WorldObject;

class DamageImpact
{
public:
    DamageImpact(WorldObject* worldObject, Voxel* voxel, const glm::vec3& damageVec);

    WorldObject* worldObject();
    const WorldObject* worldObject() const;

    Voxel* voxel();
    const Voxel* voxel() const;

    const glm::vec3& damageVec() const;

    float damage() const;

    void add(const DamageImpact& damageImpact);


protected:
    WorldObject* m_worldObject;
    Voxel* m_voxel;
    glm::vec3 m_damageVec;
};

