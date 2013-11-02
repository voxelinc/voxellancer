#include "worldtree.h"

Worldtree::Worldtree():
    WorldtreeNode(0, nullptr, AABB(glm::vec3(-8, -8, -8), glm::vec3(8, 8, 8)))
{

}

Worldtree::~Worldtree() {

}

std::set<WorldtreeGeode*> Worldtree::geodesInAABB(const AABB &aabb) {
    return WorldtreeNode::geodesInAABB(aabb);
}

std::set<WorldtreeGeode*> Worldtree::geodesInAABB(const AABB &aabb, WorldtreeGeode *nodeHint) {
    if(nodeHint == nullptr || geodeHint->aabb().contains(aabb)) {
        return geodesInAABB(aabb);
    }
    else {
        return geodesInAABB(aabb, nodeHint->parent())
    }
}

void Worldtree::aabbChanged(WorldtreeGeode *geode) {
    geode->containingNode()->aabbChanged(geode);
}
