#pragma once

#include <list>
#include <glm/glm.hpp>

#include "../geometry/aabb.h"

#include "worldtreenode.h"

<<<<<<< HEAD

class PhysicalVoxelCluster;
=======
class WorldObject;
>>>>>>> cff859ff88300583de775e3bd815405838a78cdf

class WorldTree : public WorldTreeNode
{
public:
    WorldTree();
    virtual ~WorldTree();

    WorldTreeGeode *insert(WorldObject *worldObject);

    std::set<WorldTreeGeode*> geodesInAABB(const AABB &aabb) const;
    std::set<WorldTreeGeode*> geodesInAABB(const AABB &aabb, WorldTreeNode *nodeHint) const;

    void aabbChanged(WorldTreeGeode *geode);

protected:

};

