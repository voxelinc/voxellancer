#include "worldTreegeode.h"

#include "worldtreenode.h"
#include "voxel/collidablevoxelcluster.h"


WorldTreeGeode::WorldTreeGeode():
    m_voxelcluster(nullptr),
    m_containingNode(nullptr)
{

}

WorldTreeGeode::WorldTreeGeode(CollidableVoxelCluster *voxelcluster) :
    m_voxelcluster(voxelcluster),
    m_containingNode(nullptr)
{
    m_voxelcluster->setGeode(this);
}

WorldTreeGeode::~WorldTreeGeode() {

}

CollidableVoxelCluster *WorldTreeGeode::voxelcluster() {
    return m_voxelcluster;
}

const CollidableVoxelCluster *WorldTreeGeode::voxelcluster() const {
    return m_voxelcluster;
}

void WorldTreeGeode::setVoxelCluster(CollidableVoxelCluster *voxelcluster) {
    m_voxelcluster = voxelcluster;
}

WorldTreeNode *WorldTreeGeode::containingNode() {
    return m_containingNode;
}

const WorldTreeNode *WorldTreeGeode::containingNode() const {
    return m_containingNode;
}

void WorldTreeGeode::setContainingNode(WorldTreeNode *node) {
    m_containingNode = node;
}

const AABB &WorldTreeGeode::aabb() const {
    return m_aabb;
}

void WorldTreeGeode::setAABB(const AABB &aabb) {
    m_aabb = aabb;

    if(m_containingNode != nullptr) {
        m_containingNode->aabbChanged(this);
    }
}

