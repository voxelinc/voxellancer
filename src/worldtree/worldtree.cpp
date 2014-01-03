#include "worldtree.h"

#include <algorithm>
#include <iostream>

#include "utils/tostring.h"
#include "worldobject/worldobject.h"


WorldTree::WorldTree():
    m_root(new WorldTreeNode(0, nullptr, IAABB(glm::ivec3(-8, -8, -8), glm::ivec3(8, 8, 8)), nullptr))
{

}

WorldTree::~WorldTree() {
    delete m_root;
}

WorldTreeNode* WorldTree::root() {
    return m_root;
}

WorldTreeGeode* WorldTree::insert(WorldObject* worldObject) {
    worldObject->collisionDetector().setWorldTree(this);

    WorldTreeGeode* geode = new WorldTreeGeode(worldObject);
    insert(geode);

    return geode;
}

void WorldTree::insert(WorldTreeGeode* geode) {
    if (m_root->aabb().contains(geode->aabb())) {
        m_root->insert(geode);
    } else {
        extend(geode->aabb());
        insert(geode);
    }
}

void WorldTree::remove(WorldTreeGeode* geode) {
    geode->containingNode()->remove(geode);

}

void WorldTree::aabbChanged(WorldTreeGeode* geode) {
    assert(geode->containingNode());

    WorldTreeNode* newContainingNode = containingNode(geode->aabb(), geode->containingNode());

    if (newContainingNode != geode->containingNode() || !newContainingNode->isLeaf()) {
        geode->intersectingLeafs().remove_if([&](WorldTreeNode* intersectingLeaf) {
            if (!intersectingLeaf->aabb().intersects(geode->aabb())) {
                intersectingLeaf->remove(geode);
                return true;
            }
            return false;
        });
        newContainingNode->insert(geode);
    }

    geode->setContainingNode(newContainingNode);
}

void WorldTree::extend(const IAABB& aabb) {
    assert(!m_root->aabb().contains(aabb));

    IAABB newRootAABB(m_root->aabb());

    for(int a = 0; a < 3; a++) {
        Axis axis = (Axis)a;
        int extentDir = aabb.axisMin(axis) <= m_root->aabb().axisMin(axis) ? -1 : 1;

        newRootAABB.expand(axis, extentDir * m_root->aabb().extent(axis));
    }

    m_root = new WorldTreeNode(0, nullptr, newRootAABB, m_root);
}

WorldTreeNode* WorldTree::containingNode(const IAABB& aabb, WorldTreeNode* node) {
    if(node->aabb().contains(aabb)) {
        return node;
    } else {
        if (node->parent() != nullptr) {
            return containingNode(aabb, node->parent());
        } else {
            assert(node == m_root);
            extend(aabb);
            return containingNode(aabb, m_root);
        }
    }
}
