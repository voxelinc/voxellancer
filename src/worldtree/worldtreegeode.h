#pragma once

#include <list>

#include <glow/Referenced.h>

#include "geometry/aabb.h"

#include "utils/handle/handle.h"

#include "worldtreehint.h"


class WorldTreeNode;
class WorldObject;

class WorldTreeGeode : public glow::Referenced {
public:
    WorldTreeGeode(WorldObject* worldObject);
    virtual ~WorldTreeGeode();

    WorldObject* worldObject();

    WorldTreeHint& hint();
    void setHint(const WorldTreeHint& hint);

    const IAABB& aabb() const;
    void setAABB(const IAABB& aabb);

    std::list<WorldTreeNode*>& intersectingLeafs();
    void addIntersectingLeaf(WorldTreeNode* leaf);
    void removeIntersectingLeaf(WorldTreeNode* leaf);

    bool isPassive();


protected:
    Handle<WorldObject> m_worldObject;
    WorldTreeHint m_hint;
    IAABB m_aabb;
    bool m_passive;
    std::list<WorldTreeNode*> m_intersectingLeafs;
};

