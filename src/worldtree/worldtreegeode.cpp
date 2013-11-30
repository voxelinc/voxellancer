#include "worldtreegeode.h"

#include "worldtreenode.h"
#include "world/worldobject.h"

WorldTreeGeode::WorldTreeGeode():
    m_worldobject(nullptr),
    m_containingNode(nullptr)
{

}

WorldTreeGeode::WorldTreeGeode(WorldObject *worldobject) :
    m_worldobject(worldobject),
    m_containingNode(nullptr)
{
    m_worldobject->collisionDetector()->setGeode(this);
}

WorldTreeGeode::~WorldTreeGeode() {

}

CollidableVoxelCluster *WorldTreeGeode::worldobject() {
    return m_voxelcluster;
}

const CollidableVoxelCluster *WorldTreeGeode::worldobject() const {
    return m_voxelcluster;
}

void WorldTreeGeode::setWorldObject(CollidableVoxelCluster *voxelcluster) {
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

