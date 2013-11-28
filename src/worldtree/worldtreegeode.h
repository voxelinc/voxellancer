#pragma once

#include "geometry/aabb.h"

class WorldTreeNode;
class CollidableVoxelCluster;

class WorldTreeGeode
{
public:
    WorldTreeGeode();
    WorldTreeGeode(CollidableVoxelCluster *voxelcluster);
    virtual ~WorldTreeGeode();

    CollidableVoxelCluster *voxelcluster();
    const CollidableVoxelCluster *voxelcluster() const;
    void setVoxelCluster(CollidableVoxelCluster *voxelcluster);

    WorldTreeNode *containingNode();
    const WorldTreeNode *containingNode() const;
    void setContainingNode(WorldTreeNode *node);

    const AABB &aabb() const;
    void setAABB(const AABB &aabb);

protected:
    CollidableVoxelCluster *m_voxelcluster;
    WorldTreeNode *m_containingNode;
    AABB m_aabb;
};

