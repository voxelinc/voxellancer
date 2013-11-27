#include "collidablevoxelcluster.h"
#include "worldtree/worldtreegeode.h"
#include "collision/collisiondetector.h"


CollidableVoxelCluster::CollidableVoxelCluster(glm::vec3 center, float scale) :
VoxelCluster(center, scale),
m_voxelTree(nullptr, *this, Grid3dAABB(glm::ivec3(0, 0, 0), glm::ivec3(0, 0, 0))),
m_worldTree(nullptr),
m_geode(nullptr)
{

}

CollidableVoxelCluster::~CollidableVoxelCluster() {
    //TODO: all the cleanup?
}

void CollidableVoxelCluster::addVoxel(Voxel *voxel) {
    VoxelCluster::addVoxel(voxel);
    // TODO Memoryleak as of now, voxeltree shouldn't manage the voxel
    m_voxelTree.insert(voxel);
    updateGeode();
}

void CollidableVoxelCluster::removeVoxel(const cvec3 & position) {
    VoxelCluster::removeVoxel(position);
    m_voxelTree.remove(position);
    // TODO: who deletes the voxel?
}

VoxeltreeNode &CollidableVoxelCluster::voxeltree() {
    return m_voxelTree;
}

const VoxeltreeNode &CollidableVoxelCluster::voxeltree() const {
    return m_voxelTree;
}

WorldtreeGeode *CollidableVoxelCluster::geode() {
    return m_geode;
}

const WorldtreeGeode *CollidableVoxelCluster::geode() const {
    return m_geode;
}

void CollidableVoxelCluster::setGeode(WorldtreeGeode *geode) {
    m_geode = geode;
    updateGeode();
}

void CollidableVoxelCluster::updateGeode() {
    if (m_geode != nullptr) {
        m_geode->setAABB(aabb());
    }
}

void CollidableVoxelCluster::setWorldTree(Worldtree* worldTree) {
    m_worldTree = worldTree;
    m_collisionDetector = std::unique_ptr<CollisionDetector>(new CollisionDetector(*worldTree, *this));
}

Worldtree* CollidableVoxelCluster::worldTree(){
    return m_worldTree;
}

void CollidableVoxelCluster::finishInitialization() {
    updateGeode();
    VoxelCluster::finishInitialization();
}
