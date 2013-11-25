#pragma once

#include <list>

#include "worldtree/worldtree.h"

#include "collision.h"

class WorldTreeVoxelCluster;
class VoxeltreeNode;

class CollisionDetector
{
public:
    CollisionDetector(Worldtree &worldtree, WorldTreeVoxelCluster &voxelcluster);
    virtual ~CollisionDetector();

    const std::list<Collision> &checkCollisions();
    const std::list<Collision> &lastCollisions() const;
    void reset();

protected:
    Worldtree &m_worldtree;
    WorldTreeVoxelCluster &m_voxelcluster;
    WorldTreeVoxelCluster *m_otherVoxelCluster;
    std::list<Collision> m_collisions;

    void checkCollisions(VoxeltreeNode* nodeA, VoxeltreeNode* nodeB);
};

