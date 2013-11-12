#pragma once

#include "voxel/voxelcluster.h"
#include "geometry/aabb.h"

class WorldtreeNode;

class WorldtreeGeode
{
public:
    WorldtreeGeode();
    virtual ~WorldtreeGeode();

    VoxelCluster *voxelcluster();
    const VoxelCluster *voxelcluster() const;
    void setVoxelcluster(VoxelCluster *voxelcluster);

    WorldtreeNode *containingNode();
    const WorldtreeNode *containingNode() const;
    void setContainingNode(WorldtreeNode *node);

    const AABB &aabb() const;
    void setAABB(const AABB &aabb);

protected:
    VoxelCluster *m_voxelcluster;
    WorldtreeNode *m_containingNode;
    AABB m_aabb;
};

