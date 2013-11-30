#include "impact.h"

Impact::Impact(WorldObject* worldObject, Voxel *voxel, const glm::ivec3 &vec):
    m_worldObject(worldObject),
    m_voxel(voxel),
    m_vec(vec)
{
}

WorldObject *Impact::worldObject() {
    return m_worldObject;
}

Voxel *Impact::voxel() {
    return m_voxel;
}

const glm::ivec3 &Impact::vec() const {
    return m_vec;
}
