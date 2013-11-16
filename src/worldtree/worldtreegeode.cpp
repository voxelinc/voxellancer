#include "worldtreegeode.h"

#include "worldtreenode.h"


WorldtreeGeode::WorldtreeGeode():
    m_voxelcluster(nullptr),
    m_containingNode(nullptr)
{

}


WorldtreeGeode::WorldtreeGeode(VoxelCluster *voxelcluster):
    m_voxelcluster(voxelcluster),
    m_containingNode(nullptr)
{
    m_voxelcluster->setGeode(this);
}

WorldtreeGeode::~WorldtreeGeode() {

}

VoxelCluster *WorldtreeGeode::voxelcluster() {
    return m_voxelcluster;
}

const VoxelCluster *WorldtreeGeode::voxelcluster() const {
    return m_voxelcluster;
}

void WorldtreeGeode::setVoxelCluster(VoxelCluster *voxelcluster) {
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

