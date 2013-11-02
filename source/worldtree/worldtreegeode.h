#pragma once

#include "voxelcluster.h"

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

protected:
    Voxelcluster *m_voxelcluster;
    WorldtreeNode *m_containingNode;
};
