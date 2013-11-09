#include "voxelcluster.h"

#include "worldtree/worldtreegeode.h"


Voxelcluster::Voxelcluster():
    m_voxeltree(nullptr, *this, IAABB(glm::ivec3(0, 0, 0), glm::ivec3(1, 1, 1)))
{

}

Voxelcluster::~Voxelcluster() {

}

const AABB &Voxelcluster::aabb() {
    return m_aabb;
}

const glm::vec3 &Voxelcluster::center() const {
    return m_center;
}

void Voxelcluster::setCenter(const glm::vec3 &center) {
    m_center = center;
}

const WorldTransform &Voxelcluster::worldTransform() const {
    return m_worldTransform;
}

void Voxelcluster::setWorldTransform(const WorldTransform &transform) {
    m_worldTransform = transform;
}

VoxeltreeNode &Voxelcluster::voxeltree() {
    return m_voxeltree;
}

const VoxeltreeNode &Voxelcluster::voxeltree() const {
    return m_voxeltree;
}

WorldtreeGeode *Voxelcluster::geode() {
    return m_geode;
}

const WorldtreeGeode *Voxelcluster::geode() const {
    return m_geode;
}

void Voxelcluster::setGeode(WorldtreeGeode *geode) {
    m_geode = geode;
}

