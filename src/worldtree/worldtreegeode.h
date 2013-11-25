#pragma once

#include "geometry/aabb.h"

class WorldtreeNode;
class WorldTreeVoxelCluster;

class WorldtreeGeode
{
public:
    WorldtreeGeode();
    WorldtreeGeode(WorldTreeVoxelCluster *voxelcluster);
    virtual ~WorldtreeGeode();

    WorldTreeVoxelCluster *voxelcluster();
    const WorldTreeVoxelCluster *voxelcluster() const;
    void setVoxelCluster(WorldTreeVoxelCluster *voxelcluster);

    WorldtreeNode *containingNode();
    const WorldtreeNode *containingNode() const;
    void setContainingNode(WorldtreeNode *node);

    const AABB &aabb() const;
    void setAABB(const AABB &aabb);

protected:
    WorldTreeVoxelCluster *m_voxelcluster;
    WorldtreeNode *m_containingNode;
    AABB m_aabb;
};

