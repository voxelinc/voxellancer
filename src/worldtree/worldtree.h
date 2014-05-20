#pragma once

#include <list>
#include <glm/glm.hpp>

#include "geometry/aabb.h"


class WorldTreeNode;
class WorldObject;
class WorldTreeGeode;

class WorldTree
{
public:
    WorldTree();
    virtual ~WorldTree();

    WorldTreeNode* root();

    WorldTreeGeode* insert(WorldObject* worldObject);
    void remove(WorldObject* worldObject);

    void insert(WorldTreeGeode* geode);
    void remove(WorldTreeGeode* geode);

    void aabbChanged(WorldTreeGeode* geode);


protected:
    WorldTreeNode* m_root;

    void extend(const IAABB& aabb);
    WorldTreeNode* containingNode(const IAABB& aabb, WorldTreeNode* node);
};

