#include "worldtreegeode.h"

#include "worldtreenode.h"
#include "voxel/collidablevoxelcluster.h"


WorldtreeGeode::WorldtreeGeode():
    m_voxelcluster(nullptr),
    m_containingNode(nullptr)
{

}

WorldtreeGeode::WorldtreeGeode(CollidableVoxelCluster *voxelcluster) :
    m_voxelcluster(voxelcluster),
    m_containingNode(nullptr)
{
    m_voxelcluster->setGeode(this);
}

WorldtreeGeode::~WorldtreeGeode() {

}

CollidableVoxelCluster *WorldtreeGeode::voxelcluster() {
    return m_voxelcluster;
}

const CollidableVoxelCluster *WorldtreeGeode::voxelcluster() const {
    return m_voxelcluster;
}

void WorldtreeGeode::setVoxelCluster(CollidableVoxelCluster *voxelcluster) {
    m_voxelcluster = voxelcluster;
}

WorldtreeNode *WorldtreeGeode::containingNode() {
    return m_containingNode;
}

const WorldtreeNode *WorldtreeGeode::containingNode() const {
    return m_containingNode;
}

void WorldtreeGeode::setContainingNode(WorldtreeNode *node) {
    m_containingNode = node;
}

const AABB &WorldtreeGeode::aabb() const {
    return m_aabb;
}

void WorldtreeGeode::setAABB(const AABB &aabb) {
    m_aabb = aabb;

    if(m_containingNode != nullptr) {
        m_containingNode->aabbChanged(this);
    }
}

