#pragma once

#include <list>

#include "geometry/aabb.h"


class WorldTreeNode;
class WorldObject;

class WorldTreeGeode
{
public:
    WorldTreeGeode(WorldObject* worldObject);
    virtual ~WorldTreeGeode();

    WorldObject* worldObject();
    const WorldObject* worldObject() const;
    void setWorldObject(WorldObject* worldObject);

    WorldTreeNode* containingNode();
    const WorldTreeNode* containingNode() const;
    void setContainingNode(WorldTreeNode* node);

    const IAABB& aabb() const;
    void setAABB(const IAABB& aabb);

    std::list<WorldTreeNode*>& intersectingLeafs();
    void addIntersectingLeaf(WorldTreeNode* leaf);
    void removeIntersectingLeaf(WorldTreeNode* leaf);


protected:
    WorldObject* m_worldObject;
    WorldTreeNode* m_containingNode;
    IAABB m_aabb;
    std::list<WorldTreeNode*> m_intersectingLeafs;
};

