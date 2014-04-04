#pragma once

#include <list>

#include "geometry/aabb.h"

#include "worldtreehint.h"


class WorldTreeNode;
class WorldObject;

class WorldTreeGeode
{
public:
    WorldTreeGeode(WorldObject* worldObject);
    virtual ~WorldTreeGeode();

    WorldObject* worldObject();
    void setWorldObject(WorldObject* worldObject);

    WorldTreeHint& worldTreeHint();
    void setWorldTreeHint(const WorldTreeHint& worldTreeHint);

    const IAABB& aabb() const;
    void setAABB(const IAABB& aabb);

    std::list<WorldTreeNode*>& intersectingLeafs();
    void addIntersectingLeaf(WorldTreeNode* leaf);
    void removeIntersectingLeaf(WorldTreeNode* leaf);

    bool isPassive();


protected:
    WorldObject* m_worldObject;
    WorldTreeHint m_worldTreeHint;
    IAABB m_aabb;
    bool m_passive;
    std::list<WorldTreeNode*> m_intersectingLeafs;
};

