#pragma once

#include <list>

#include "worldtree/worldtree.h"

#include "collision.h"

class PhysicalVoxelCluster;
class VoxeltreeNode;

class CollisionDetector
{
public:
    CollisionDetector(Worldtree &worldtree, PhysicalVoxelCluster &voxelcluster);
    virtual ~CollisionDetector();

    const std::list<Collision> &checkCollisions();


protected:
    Worldtree &m_worldtree;
    PhysicalVoxelCluster &m_voxelcluster;
    std::list<Collision> m_collisions;

    void checkCollisions(VoxeltreeNode* nodeA, VoxeltreeNode* nodeB);
};

