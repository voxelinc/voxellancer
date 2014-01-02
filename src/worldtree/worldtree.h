#pragma once

#include <list>
#include <glm/glm.hpp>

#include "geometry/aabb.h"

#include "worldtreenode.h"


class WorldObject;

class WorldTree
{
public:
    WorldTree();
    ~WorldTree();

    WorldTreeNode* root();

    WorldTreeGeode* insert(WorldObject* worldObject);
    void insert(WorldTreeGeode* geode);
    void remove(WorldTreeGeode* geode);

    void aabbChanged(WorldTreeGeode* geode);


protected:
    WorldTreeNode* m_root;

    void extent(const IAABB& aabb);
    WorldTreeNode* containingNode(const IAABB& aabb, WorldTreeNode* node);
};

