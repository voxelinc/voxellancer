#include "worldtreegeode.h"

#include "physics/physicalvoxelcluster.h"

#include "worldtreenode.h"


WorldTreeGeode::WorldTreeGeode():
    m_voxelcluster(nullptr),
    m_containingNode(nullptr)
{

}

WorldTreeGeode::WorldTreeGeode(PhysicalVoxelCluster *voxelcluster) :
    m_voxelcluster(voxelcluster),
    m_containingNode(nullptr)
{
    m_voxelcluster->setGeode(this);
}

WorldTreeGeode::~WorldTreeGeode() {

}

PhysicalVoxelCluster *WorldTreeGeode::voxelcluster() {
    return m_voxelcluster;
}

const PhysicalVoxelCluster *WorldTreeGeode::voxelcluster() const {
    return m_voxelcluster;
}

void WorldTreeGeode::setVoxelCluster(PhysicalVoxelCluster *voxelcluster) {
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

