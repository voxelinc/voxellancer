#pragma once

#include <list>

#include "worldtree/worldtree.h"

#include "collision.h"


class PhysicalVoxelCluster;
class VoxelTreeNode;

class CollisionDetector
{
public:
    CollisionDetector(WorldTree& worldTree, PhysicalVoxelCluster &physicalVoxelCluster);

    std::list<Collision>& checkCollisions();
    std::list<Collision>& lastCollisions();

    void reset();


protected:
    WorldTree& m_worldTree;
    PhysicalVoxelCluster& m_voxelcluster;
    PhysicalVoxelCluster* m_otherVoxelCluster;
    std::list<Collision> m_collisions;

    void checkCollisions(VoxelTreeNode* nodeA, VoxelTreeNode* nodeB);
};

