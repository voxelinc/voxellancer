#include "worldtreegeode.h"

#include "physics/physicalvoxelcluster.h"

#include "worldtreenode.h"

#include "world/worldObject.h"

WorldTreeGeode::WorldTreeGeode():
    m_worldObject(nullptr),
    m_containingNode(nullptr)
{

}

WorldTreeGeode::WorldTreeGeode(WorldObject *worldObject) :
    m_worldObject(worldObject),
    m_containingNode(nullptr)
{
    m_worldObject->collisionDetector()->setGeode(this);
}

WorldTreeGeode::~WorldTreeGeode() {

}

WorldObject *WorldTreeGeode::worldObject() {
    return m_voxelcluster;
}

const WorldObject *WorldTreeGeode::worldObject() const {
    return m_voxelcluster;
}

void WorldTreeGeode::setWorldObject(WorldObject *worldObject) {
    m_worldObject = worldObject;
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

