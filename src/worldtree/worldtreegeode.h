#pragma once

#include "voxelcluster.h"
#include "geometry/aabb.h"

class WorldtreeNode;

class WorldtreeGeode
{
public:
    WorldtreeGeode();
    virtual ~WorldtreeGeode();

    Voxelcluster *voxelcluster();
    const Voxelcluster *voxelcluster() const;
    void setVoxelcluster(Voxelcluster *voxelcluster);

    WorldtreeNode *containingNode();
    const WorldtreeNode *containingNode() const;
    void setContainingNode(WorldtreeNode *node);

    const AABB &aabb() const;
    void setAABB(const AABB &aabb);

protected:
    Voxelcluster *m_voxelcluster;
    WorldtreeNode *m_containingNode;
    AABB m_aabb;
};

