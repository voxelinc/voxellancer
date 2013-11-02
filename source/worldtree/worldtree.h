#pragma once

#include <list>
#include <glm/glm.hpp>

#include "geometry/aabb.h"

#include "worldtreenode.h"

class Worldtree : public WorldtreeNode
{
public:
    Worldtree();
    virtual ~Worldtree();

    void remove(WorldtreeGeode *geode);

    std::set<WorldtreeGeode*> geodesInAABB(const AABB &aabb);
    std::set<WorldtreeGeode*> geodesInAABB(const AABB &aabb, WorldtreeNode *nodeHint);

    void aabbChanged(WorldtreeGeode *geode);

protected:

};

