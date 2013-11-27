#include "worldtree.h"

#include <iostream>

#include "worldtreecluster.h"
#include "utils/tostring.h"


Worldtree::Worldtree():
    WorldtreeNode(0, nullptr, AABB(glm::vec3(-8, -8, -8), glm::vec3(8, 8, 8)))
{

}

Worldtree::~Worldtree() {

}

WorldtreeGeode *Worldtree::insert(WorldTreeVoxelCluster *voxelcluster) {
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

