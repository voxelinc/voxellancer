#include "worldtreegeode.h"

#include <cassert>

#include "collision/collisiondetector.h"

#include "voxel/voxelclusterbounds.h"

#include "worldobject/worldobject.h"

#include "worldtreenode.h"


WorldTreeGeode::WorldTreeGeode(WorldObject* worldObject) :
    m_worldObject(makeHandle(worldObject)),
    m_aabb(worldObject->bounds().aabb()),
    m_passive(false)
{
    m_worldObject->collisionDetector().setGeode(this);
    if (worldObject->passiveForCollisionDetection()) {
        m_passive = true;
    }
}

WorldTreeGeode::~WorldTreeGeode() = default;

WorldObject* WorldTreeGeode::worldObject() {
    assert(m_worldObject.valid());
    return m_worldObject.get();
}

WorldTreeHint& WorldTreeGeode::hint() {
    return m_hint;
}

void WorldTreeGeode::setHint(const WorldTreeHint& hint) {
    m_hint = hint;
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


