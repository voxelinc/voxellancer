#pragma once

#include <list>
#include <glm/glm.hpp>

#include "../geometry/aabb.h"

#include "worldtreenode.h"

class CollidableVoxelCluster;

class WorldTree : public WorldTreeNode
{
public:
    WorldTree();
    virtual ~WorldTree();

    WorldTreeGeode *insert(CollidableVoxelCluster *voxelcluster);

    std::set<WorldTreeGeode*> geodesInAABB(const AABB &aabb) const;
    std::set<WorldTreeGeode*> geodesInAABB(const AABB &aabb, WorldTreeNode *nodeHint) const;

    void aabbChanged(WorldTreeGeode *geode);

protected:

};

