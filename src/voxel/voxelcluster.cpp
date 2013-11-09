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

