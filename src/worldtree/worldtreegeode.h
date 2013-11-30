#pragma once

#include "geometry/aabb.h"

class WorldTreeNode;
class PhysicalVoxelCluster;

class WorldTreeGeode
{
public:
    WorldTreeGeode();
    WorldTreeGeode(PhysicalVoxelCluster *voxelcluster);
    virtual ~WorldTreeGeode();

    PhysicalVoxelCluster *voxelcluster();
    const PhysicalVoxelCluster *voxelcluster() const;
    void setVoxelCluster(PhysicalVoxelCluster *voxelcluster);

    WorldTreeNode *containingNode();
    const WorldTreeNode *containingNode() const;
    void setContainingNode(WorldTreeNode *node);

    const AABB &aabb() const;
    void setAABB(const AABB &aabb);


protected:
    PhysicalVoxelCluster *m_voxelcluster;
    WorldTreeNode *m_containingNode;
    AABB m_aabb;
};

