#include "worldtreecluster.h"
#include "worldtree/worldtreegeode.h"
#include "collision/collisiondetector.h"


WorldTreeVoxelCluster::WorldTreeVoxelCluster(glm::vec3 center, float scale) :
VoxelCluster(center, scale),
m_voxelTree(nullptr, *this, Grid3dAABB(glm::ivec3(0, 0, 0), glm::ivec3(0, 0, 0))),
m_worldTree(nullptr),
m_geode(nullptr),
m_collisionDetector(nullptr)
{

}

WorldTreeVoxelCluster::WorldTreeVoxelCluster(const WorldTreeVoxelCluster& other) :
VoxelCluster(other),
m_voxelTree(other.m_voxelTree, this),
m_worldTree(nullptr),
m_geode(nullptr),
m_collisionDetector(nullptr) 
{
}

WorldTreeVoxelCluster::~WorldTreeVoxelCluster() {

}

void WorldTreeVoxelCluster::addVoxel(const Voxel & voxel) {
    VoxelCluster::addVoxel(voxel);
    // TODO Memoryleak as of now, voxeltree shouldn't manage the voxel
    m_voxelTree.insert(new Voxel(voxel));
    updateGeode();
}

void WorldTreeVoxelCluster::removeVoxel(const cvec3 & position) {
    VoxelCluster::removeVoxel(position);
    m_voxelTree.remove(position);
}

VoxeltreeNode &WorldTreeVoxelCluster::voxeltree() {
    return m_voxelTree;
}

const VoxeltreeNode &WorldTreeVoxelCluster::voxeltree() const {
    return m_voxelTree;
}

WorldtreeGeode *WorldTreeVoxelCluster::geode() {
    return m_geode;
}

const WorldtreeGeode *WorldTreeVoxelCluster::geode() const {
    return m_geode;
}

void WorldTreeVoxelCluster::setGeode(WorldtreeGeode *geode) {
    m_geode = geode;
    updateGeode();
}

void WorldTreeVoxelCluster::updateGeode() {
    if (m_geode != nullptr) {
        m_geode->setAABB(aabb());
    }
}

void WorldTreeVoxelCluster::setWorldTree(Worldtree* worldTree) {
    m_worldTree = worldTree;
    m_collisionDetector = std::unique_ptr<CollisionDetector>(new CollisionDetector(*worldTree, *this));
}

Worldtree* WorldTreeVoxelCluster::worldTree(){
    return m_worldTree;
}

void WorldTreeVoxelCluster::finishInitialization() {
    updateGeode();
    VoxelCluster::finishInitialization();
}
