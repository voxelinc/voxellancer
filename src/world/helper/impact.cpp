#include "impact.h"

#include <cassert>


Impact::Impact(WorldObject* worldObject, Voxel *voxel, const glm::vec3 &vec):
    m_worldObject(worldObject),
    m_voxel(voxel),
    m_vec(vec)
{
}

WorldObject *Impact::worldObject() {
    return m_worldObject;
}

const WorldObject *Impact::worldObject() const {
    return m_worldObject;
}

Voxel *Impact::voxel() {
    return m_voxel;
}

const Voxel *Impact::voxel() const {
    return m_voxel;
}

const glm::vec3 &Impact::vec() const {
    return m_vec;
}

void Impact::add(const Impact& impact) {
    assert(impact.voxel() == m_voxel);
    assert(impact.worldObject() == m_worldObject);

    m_vec += impact.vec();
}

