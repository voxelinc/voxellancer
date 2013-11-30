
#include "worldtree/worldtreegeode.h"
#include "collision/collisiondetector.h"

<<<<<<< HEAD
#include "utils/tostring.h"

#include "world/worldobject.h"

#include "physics/physicalvoxel.h"
#include "physics/physicalvoxelcluster.h"
=======

CollisionDetector::CollisionDetector(WorldObject & worldObject) :
    m_voxelTree(nullptr, &WorldObject, Grid3dAABB(glm::ivec3(0, 0, 0), glm::ivec3(0, 0, 0))),
    m_worldTree(nullptr),
    m_geode(nullptr)
{
>>>>>>> cff859ff88300583de775e3bd815405838a78cdf


<<<<<<< HEAD
CollisionDetector::CollisionDetector(WorldTree &worldTree, PhysicalVoxelCluster &voxelcluster) :
    m_worldTree(worldTree),
    m_voxelcluster(voxelcluster),
    m_otherVoxelCluster(nullptr)
{
=======
CollisionDetector::~CollisionDetector() {
}
>>>>>>> cff859ff88300583de775e3bd815405838a78cdf

void CollisionDetector::addVoxel(Voxel *voxel) {
    VoxelCluster::addVoxel(voxel);
    m_voxelTree.insert(voxel);
}

void CollisionDetector::removeVoxel(const cvec3 & position) {
    m_voxelTree.remove(position);
    VoxelCluster::removeVoxel(position);
}

VoxelTreeNode &CollisionDetector::voxeltree() {
    return m_voxelTree;
}

const VoxelTreeNode &CollisionDetector::voxeltree() const {
    return m_voxelTree;
}

WorldTreeGeode *CollisionDetector::geode() {
    return m_geode;
}

const WorldTreeGeode *CollisionDetector::geode() const {
    return m_geode;
}

<<<<<<< HEAD
void CollisionDetector::checkCollisions(VoxelTreeNode* nodeA, VoxelTreeNode* nodeB) {
        return;
    }
    if(nodeB->isLeaf() && nodeB->voxel() == nullptr) {
        return;
    }
=======
void CollisionDetector::setGeode(WorldTreeGeode *geode) {
    m_geode = geode;
    updateGeode();
}
>>>>>>> cff859ff88300583de775e3bd815405838a78cdf

void CollisionDetector::updateGeode() {
    if (m_geode != nullptr) {
        m_geode->setAABB(aabb());
    }
}

void CollisionDetector::setWorldTree(WorldTree* worldTree) {
    m_worldTree = worldTree;
    m_collisionDetector = std::unique_ptr<CollisionDetector>(new CollisionDetector(*worldTree, *this));
}

WorldTree* CollisionDetector::worldTree(){
    return m_worldTree;
}

void CollisionDetector::finishInitialization() {
    updateGeode();
}
