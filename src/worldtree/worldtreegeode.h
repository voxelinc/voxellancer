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

    WorldObject *worldObject();
    const WorldObject *worldObject() const;
    void setWorldObject(WorldObject *worldObject);

    WorldTreeNode *containingNode();
    const WorldTreeNode *containingNode() const;
    void setContainingNode(WorldTreeNode *node);

    const AABB &aabb() const;
    void setAABB(const AABB &aabb);


protected:
    WorldObject *m_worldobject;
    WorldTreeNode *m_containingNode;
    AABB m_aabb;
};

