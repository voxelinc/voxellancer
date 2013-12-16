#pragma once

#include <glm/glm.hpp>


class Voxel;
class WorldObject;

class Impact
{
public:
    Impact(WorldObject* worldObject, Voxel *voxel, const glm::vec3 &vec);

    WorldObject *worldObject();
    const WorldObject *worldObject() const;

    Voxel *voxel();
    const Voxel *voxel() const;

    const glm::vec3 &vec() const;

    void add(const Impact& impact);


protected:
    WorldObject *m_worldObject;
    Voxel *m_voxel;
    glm::vec3 m_vec;
};
