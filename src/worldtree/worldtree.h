#pragma once

#include <list>
#include <glm/glm.hpp>

#include "../geometry/aabb.h"

#include "worldtreenode.h"

class Worldtree : public WorldtreeNode
{
public:
    Worldtree();
    virtual ~Worldtree();

    WorldtreeGeode *insert(WorldTreeVoxelCluster *voxelcluster);

    std::set<WorldtreeGeode*> geodesInAABB(const AABB &aabb) const;
    std::set<WorldtreeGeode*> geodesInAABB(const AABB &aabb, WorldtreeNode *nodeHint) const;

    void aabbChanged(WorldtreeGeode *geode);

protected:

};

