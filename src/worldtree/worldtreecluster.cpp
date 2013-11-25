#include "worldtreecluster.h"
#include "worldtree/worldtreegeode.h"


WorldTreeCluster::WorldTreeCluster(glm::vec3 center, float scale) :
VoxelCluster(center, scale),
m_voxelTree(nullptr, *this, Grid3dAABB(glm::ivec3(0, 0, 0), glm::ivec3(0, 0, 0))),
m_geode(nullptr)
{

}

WorldTreeCluster::WorldTreeCluster(const WorldTreeCluster& other) :
VoxelCluster(other),
m_voxelTree(other.m_voxelTree, this),
m_geode(nullptr)
{
}

WorldTreeCluster::~WorldTreeCluster() {

}

void WorldTreeCluster::addVoxel(const Voxel & voxel) {
    VoxelCluster::addVoxel(voxel);
    // TODO Memoryleak as of now, voxeltree shouldn't manage the voxel
    m_voxelTree.insert(new Voxel(voxel));
    updateGeode();
}

void WorldTreeCluster::removeVoxel(const cvec3 & position) {
    VoxelCluster::removeVoxel(position);
    m_voxelTree.remove(position);
}

VoxeltreeNode &WorldTreeCluster::voxeltree() {
    return m_voxelTree;
}

const VoxeltreeNode &WorldTreeCluster::voxeltree() const {
    return m_voxelTree;
}

WorldtreeGeode *WorldTreeCluster::geode() {
    return m_geode;
}

const WorldtreeGeode *WorldTreeCluster::geode() const {
    return m_geode;
}

void WorldTreeCluster::setGeode(WorldtreeGeode *geode) {
    m_geode = geode;

    updateGeode();
}

void WorldTreeCluster::updateGeode() {
    if (m_geode != nullptr) {
        m_geode->setAABB(aabb());
    }
}

void WorldTreeCluster::setWorldTree(Worldtree* worldTree) {
    m_worldTree = worldTree;
}