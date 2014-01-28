#pragma once

#include <set>
#include <list>
#include <memory>
#include <unordered_map>

#include <glm/glm.hpp>

#include "collision/voxelcollision.h"

class Voxel;
class WorldTree;
class WorldTreeGeode;
class WorldObject;
class Sphere;
class VoxelTree;
class VoxelTreeNode;

// this class contains datastructures for collision detection
class CollisionDetector
{
public:
    CollisionDetector(WorldObject& worldObject);
    ~CollisionDetector();

    void addVoxel(Voxel* voxel);
    void removeVoxel(Voxel* voxel);

    std::list<VoxelCollision> &checkCollisions();
    std::list<VoxelCollision> &lastCollisions();

    void reset();

    WorldTreeGeode* geode();
    void setGeode(WorldTreeGeode* geode);

    void setWorldTree(WorldTree* worldTree);
    WorldTree* worldTree();

    VoxelTree& voxelTree();

    void updateGeode();


protected:
    std::shared_ptr<VoxelTree> m_voxelTree;
    WorldObject& m_worldObject;
    WorldTreeGeode* m_geode;
    WorldTree* m_worldTree;
    std::list<VoxelCollision> m_collisions;

    void checkCollisions(VoxelTreeNode* nodeA, VoxelTreeNode* nodeB);
    const Sphere& getOrCreateSphere(VoxelTreeNode* node);
};

