#pragma once

#include <list>

#include "collision.h"

#include "voxel/voxelcluster.h"

#include "worldtree/worldtree.h"


class CollisionDetector
{
public:
    CollisionDetector(Worldtree &worldtree, Voxelcluster &voxelcluster);
    virtual ~CollisionDetector();

    const std::list<Collision> &checkCollisions();


protected:
    Worldtree &m_worldtree;
    Voxelcluster &m_voxelcluster;
    std::list<Collision> m_collisions;

    void checkCollisions(VoxeltreeNode* nodeA, VoxeltreeNode* nodeB);
};

