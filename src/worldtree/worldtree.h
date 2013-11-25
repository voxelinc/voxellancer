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

    void insert(WorldtreeGeode *geode);
    WorldtreeGeode *insert(WorldTreeVoxelCluster *voxelcluster);
    void remove(WorldtreeGeode *geode);

    std::set<WorldtreeGeode*> geodesInAABB(const AABB &aabb) const;
    std::set<WorldtreeGeode*> geodesInAABB(const AABB &aabb, WorldtreeNode *nodeHint) const;

    void aabbChanged(WorldtreeGeode *geode);

protected:

};

