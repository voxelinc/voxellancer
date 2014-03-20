#include "worldtreegeode.h"

#include <cassert>

#include "worldtreenode.h"
#include "worldobject/worldobject.h"
#include "collision/collisiondetector.h"
#include "voxel/voxelclusterbounds.h"


WorldTreeGeode::WorldTreeGeode(WorldObject* worldObject) :
    m_worldObject(worldObject),
    m_containingNode(nullptr),
    m_aabb(worldObject->bounds().aabb()),
    m_passive(false)
{
    m_worldObject->collisionDetector().setGeode(this);
    if (worldObject->objectType() == WorldObjectType::Bullet) {
        m_passive = true;
    }
}

WorldTreeGeode::~WorldTreeGeode() {

}

WorldObject* WorldTreeGeode::worldObject() {
    return m_worldObject;
}

const WorldObject* WorldTreeGeode::worldObject() const {
    return m_worldObject;
}

void WorldTreeGeode::setWorldObject(WorldObject* worldObject) {
    m_worldObject = worldObject;
}

WorldTreeNode* WorldTreeGeode::containingNode() {
    return m_containingNode;
}

const WorldTreeNode* WorldTreeGeode::containingNode() const {
    return m_containingNode;
}

void WorldTreeGeode::setContainingNode(WorldTreeNode* node) {
    m_containingNode = node;
}

const IAABB& WorldTreeGeode::aabb() const {
    return m_aabb;
}

void WorldTreeGeode::setAABB(const IAABB& aabb) {
    m_aabb = aabb;
}

std::list<WorldTreeNode*>& WorldTreeGeode::intersectingLeafs() {
    return m_intersectingLeafs;
}

void WorldTreeGeode::addIntersectingLeaf(WorldTreeNode* leaf) {
    assert(leaf->isLeaf());
    m_intersectingLeafs.push_back(leaf);
}

void WorldTreeGeode::removeIntersectingLeaf(WorldTreeNode* leaf) {
    m_intersectingLeafs.remove(leaf);
}

bool WorldTreeGeode::isPassive() {
    return m_passive;
}


