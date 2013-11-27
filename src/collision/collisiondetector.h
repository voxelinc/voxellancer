#pragma once

#include <list>

#include "worldtree/worldtree.h"

#include "collision.h"

class CollidableVoxelCluster;
class VoxeltreeNode;

class CollisionDetector
{
public:
    CollisionDetector(Worldtree &worldtree, CollidableVoxelCluster &voxelcluster);
    virtual ~CollisionDetector();

    std::list<Collision> &checkCollisions();
    std::list<Collision> &lastCollisions();
    void reset();

protected:
    Worldtree &m_worldtree;
    CollidableVoxelCluster &m_voxelcluster;
    CollidableVoxelCluster *m_otherVoxelCluster;
    std::list<Collision> m_collisions;

    void checkCollisions(VoxeltreeNode* nodeA, VoxeltreeNode* nodeB);
};

