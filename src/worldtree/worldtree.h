#pragma once

#include <list>
#include <glm/glm.hpp>

#include "../geometry/aabb.h"

#include "worldtreenode.h"

class WorldObject;

class WorldTree : public WorldTreeNode
{
public:
    WorldTree();
    virtual ~WorldTree();

    WorldTreeGeode *insert(WorldObject *worldObject);

    std::set<WorldTreeGeode*> geodesInAABB(const AABB& aabb, WorldTreeNode* nodeHint = nullptr, WorldObject* collideableWith = nullptr) const;
    bool areGeodesInAABB(const AABB& aabb, WorldTreeNode* nodeHint = nullptr, WorldObject* collideableWith = nullptr) const;

    void aabbChanged(WorldTreeGeode* geode);

    void poll(int& nodes, int &empty, int& geodes, int& depth);

protected:

};

