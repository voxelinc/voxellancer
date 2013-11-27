#pragma once

#include <list>

#include "worldtree/worldtree.h"

#include "collision.h"

class CollidableVoxelCluster;
class VoxelTreeNode;

class CollisionDetector
{
public:
    CollisionDetector(WorldTree &worldTree, CollidableVoxelCluster &voxelcluster);
    virtual ~CollisionDetector();

    std::list<Collision> &checkCollisions();
    std::list<Collision> &lastCollisions();
    void reset();

protected:
    WorldTree &m_worldTree;
    CollidableVoxelCluster &m_voxelcluster;
    CollidableVoxelCluster *m_otherVoxelCluster;
    std::list<Collision> m_collisions;

    void checkCollisions(VoxelTreeNode* nodeA, VoxelTreeNode* nodeB);
};

