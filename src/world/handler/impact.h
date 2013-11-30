#pragma once

#include <glm/glm.hpp>


class Voxel;
class WorldObject;

class Impact
{
public:
    Impact(WorldObject* worldObject, Voxel *voxel, const glm::ivec3 &vec);

    WorldObject *worldObject();
    Voxel *voxel();
    const glm::ivec3 &vec() const;

protected:
    WorldObject *m_worldObject
    Voxel *m_voxel;
    glm::ivec3 m_vec;
};

