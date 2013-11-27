#include "collidablevoxelcluster.h"
#include "worldTree/worldTreegeode.h"
#include "collision/collisiondetector.h"


CollidableVoxelCluster::CollidableVoxelCluster(glm::vec3 center, float scale) :
    VoxelCluster(center, scale),
    m_voxelTree(nullptr, *this, Grid3dAABB(glm::ivec3(0, 0, 0), glm::ivec3(0, 0, 0))),
    m_worldTree(nullptr),
    m_geode(nullptr)
{

}

CollidableVoxelCluster::~CollidableVoxelCluster() {
}

void CollidableVoxelCluster::addVoxel(Voxel *voxel) {
    VoxelCluster::addVoxel(voxel);
    m_voxelTree.insert(voxel);
    updateGeode();
}

void CollidableVoxelCluster::removeVoxel(const cvec3 & position) {
    m_voxelTree.remove(position);
    VoxelCluster::removeVoxel(position);
}

VoxelTreeNode &CollidableVoxelCluster::voxeltree() {
    return m_voxelTree;
}

const VoxelTreeNode &CollidableVoxelCluster::voxeltree() const {
    return m_voxelTree;
}

WorldTreeGeode *CollidableVoxelCluster::geode() {
    return m_geode;
}

const WorldTreeGeode *CollidableVoxelCluster::geode() const {
    return m_geode;
}

void CollidableVoxelCluster::setGeode(WorldTreeGeode *geode) {
    m_geode = geode;
    updateGeode();
}

void CollidableVoxelCluster::updateGeode() {
    if (m_geode != nullptr) {
        m_geode->setAABB(aabb());
    }
}

void CollidableVoxelCluster::setWorldTree(WorldTree* worldTree) {
    m_worldTree = worldTree;
    m_collisionDetector = std::unique_ptr<CollisionDetector>(new CollisionDetector(*worldTree, *this));
}

WorldTree* CollidableVoxelCluster::worldTree(){
    return m_worldTree;
}

void CollidableVoxelCluster::finishInitialization() {
    updateGeode();
    VoxelCluster::finishInitialization();
}
