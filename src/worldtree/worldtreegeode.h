#pragma once

#include "geometry/aabb.h"

class WorldtreeNode;
class WorldTreeCluster;

class WorldtreeGeode
{
public:
    WorldtreeGeode();
    WorldtreeGeode(WorldTreeCluster *voxelcluster);
    virtual ~WorldtreeGeode();

    WorldTreeCluster *voxelcluster();
    const WorldTreeCluster *voxelcluster() const;
    void setVoxelCluster(WorldTreeCluster *voxelcluster);

    WorldtreeNode *containingNode();
    const WorldtreeNode *containingNode() const;
    void setContainingNode(WorldtreeNode *node);

    const AABB &aabb() const;
    void setAABB(const AABB &aabb);

protected:
    WorldTreeCluster *m_voxelcluster;
    WorldtreeNode *m_containingNode;
    AABB m_aabb;
};

