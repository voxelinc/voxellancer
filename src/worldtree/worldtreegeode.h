#pragma once

#include "geometry/aabb.h"

class WorldtreeNode;
class WorldObject;

class WorldtreeGeode
{
public:
    WorldtreeGeode();
    WorldtreeGeode(WorldObject *voxelcluster);
    virtual ~WorldtreeGeode();

    WorldObject *voxelcluster();
    const WorldObject *voxelcluster() const;
    void setVoxelCluster(WorldObject *voxelcluster);

    WorldtreeNode *containingNode();
    const WorldtreeNode *containingNode() const;
    void setContainingNode(WorldtreeNode *node);

    const AABB &aabb() const;
    void setAABB(const AABB &aabb);

protected:
    WorldObject *m_voxelcluster;
    WorldtreeNode *m_containingNode;
    AABB m_aabb;
};

