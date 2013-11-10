#pragma once

#include <list>

#include "voxel/voxelcluster.h"

#include "worldtree/worldtree.h"

#include "collision.h"


class CollisionDetector
{
public:
    CollisionDetector(Worldtree &worldtree, VoxelCluster &voxelcluster);
    virtual ~CollisionDetector();

    const std::list<Collision> &checkCollisions();


protected:
    Worldtree &m_worldtree;
    VoxelCluster &m_voxelcluster;
    std::list<Collision> m_collisions;

    void checkCollisions(VoxeltreeNode* nodeA, VoxeltreeNode* nodeB);
};

