#pragma once

#include "geometry/aabb.h"

class WorldTreeNode;
class WorldObject;

class WorldTreeGeode
{
public:
    WorldTreeGeode();
    WorldTreeGeode(WorldObject *voxelcluster);
    virtual ~WorldTreeGeode();

    WorldObject *worldobject();
    const WorldObject *worldobject() const;
    void setWorldObject(WorldObject *worldobject);

    WorldTreeNode *containingNode();
    const WorldTreeNode *containingNode() const;
    void setContainingNode(WorldTreeNode *node);

    const AABB &aabb() const;
    void setAABB(const AABB &aabb);


protected:
    WorldObject *m_worldObject;
    WorldTreeNode *m_containingNode;
    AABB m_aabb;
};

