#include "worldtree.h"

#include <iostream>

#include "utils/tostring.h"
#include "worldobject/worldobject.h"


WorldTree::WorldTree():
    WorldTreeNode(0, nullptr, AABB(glm::vec3(-8, -8, -8), glm::vec3(8, 8, 8)))
{

}

WorldTree::~WorldTree() {

}

WorldTreeGeode *WorldTree::insert(WorldObject *worldObject) {
    WorldTreeGeode *geode = new WorldTreeGeode(worldObject);
    WorldTreeNode::insert(geode);
    worldObject->collisionDetector().setWorldTree(this);
    return geode;
}

std::set<WorldTreeGeode*> WorldTree::geodesInAABB(const AABB &aabb) const {
    return WorldTreeNode::geodesInAABB(aabb);
}

std::set<WorldTreeGeode*> WorldTree::geodesInAABB(const AABB &aabb, WorldTreeNode *nodeHint) const {
    assert(nodeHint != nullptr);

    if (nodeHint->aabb().contains(aabb)) {
        return nodeHint->geodesInAABB(aabb);
    }
    else if(nodeHint->parent() != nullptr) {
        return geodesInAABB(aabb, nodeHint->parent());
    }
    else {
        return WorldTreeNode::geodesInAABB(aabb);
    }
}

void WorldTree::aabbChanged(WorldTreeGeode *geode) {
    geode->containingNode()->aabbChanged(geode);
}

void WorldTree::poll(int& nodes, int &empty, int& geodes, int& depth) {
    nodes = empty = geodes = depth = 0;
    WorldTreeNode::poll(nodes, empty, geodes, depth);
}
