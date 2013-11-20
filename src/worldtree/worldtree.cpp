#include "worldtree.h"

#include <iostream>

#include "utils/tostring.h"


Worldtree::Worldtree():
    WorldtreeNode(0, nullptr, AABB(glm::vec3(-8, -8, -8), glm::vec3(8, 8, 8)))
{

}

Worldtree::~Worldtree() {

}

void Worldtree::insert(WorldtreeGeode *geode) {
    WorldtreeNode::insert(geode);
}

WorldtreeGeode *Worldtree::insert(VoxelCluster *voxelcluster) {
    WorldtreeGeode *geode = new WorldtreeGeode(voxelcluster);
    WorldtreeNode::insert(geode);
    voxelcluster->setWorldTree(this);
    return geode;
}

std::set<WorldtreeGeode*> Worldtree::geodesInAABB(const AABB &aabb) const {
    return WorldtreeNode::geodesInAABB(aabb);
}

std::set<WorldtreeGeode*> Worldtree::geodesInAABB(const AABB &aabb, WorldtreeNode *nodeHint) const {
    assert(nodeHint != nullptr);

    if (nodeHint->aabb().contains(aabb)) {
        return nodeHint->geodesInAABB(aabb);
    }
    else if(nodeHint->parent() != nullptr) {
        return geodesInAABB(aabb, nodeHint->parent());
    }
    else {
        return WorldtreeNode::geodesInAABB(aabb);
    }
}

void Worldtree::aabbChanged(WorldtreeGeode *geode) {
    geode->containingNode()->aabbChanged(geode);
}

