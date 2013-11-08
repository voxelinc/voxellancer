#include "worldtree.h"

Worldtree::Worldtree():
    WorldtreeNode(0, nullptr, AABB(glm::vec3(-8, -8, -8), glm::vec3(8, 8, 8)))
{

}

Worldtree::~Worldtree() {

}

std::set<WorldtreeGeode*> Worldtree::geodesInAABB(const AABB &aabb) const {
    return WorldtreeNode::geodesInAABB(aabb);
}

std::set<WorldtreeGeode*> Worldtree::geodesInAABB(const AABB &aabb, WorldtreeNode *nodeHint) const {
    if(nodeHint == nullptr ) {
        return geodesInAABB(aabb);
    }
    if (nodeHint->aabb().contains(aabb)) {
        return nodeHint->geodesInAABB(aabb);
    }
    return geodesInAABB(aabb, nodeHint->parent());
}

void Worldtree::aabbChanged(WorldtreeGeode *geode) {
    geode->containingNode()->aabbChanged(geode);
}
