#pragma once

#include "geometry/aabb.h"

class WorldtreeNode;
class CollidableVoxelCluster;

class WorldtreeGeode
{
public:
    WorldtreeGeode();
    WorldtreeGeode(CollidableVoxelCluster *voxelcluster);
    virtual ~WorldtreeGeode();

    CollidableVoxelCluster *voxelcluster();
    const CollidableVoxelCluster *voxelcluster() const;
    void setVoxelCluster(CollidableVoxelCluster *voxelcluster);

    WorldtreeNode *containingNode();
    const WorldtreeNode *containingNode() const;
    void setContainingNode(WorldtreeNode *node);

    const AABB &aabb() const;
    void setAABB(const AABB &aabb);

protected:
    CollidableVoxelCluster *m_voxelcluster;
    WorldtreeNode *m_containingNode;
    AABB m_aabb;
};

