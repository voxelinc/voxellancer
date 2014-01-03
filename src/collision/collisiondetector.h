#pragma once

#include <set>
#include <memory>
#include <unordered_map>

#include <glm/glm.hpp>

#include "voxel/voxel.h"
#include "voxel/voxeltree.h"
#include "collision/voxelcollision.h"
#include "geometry/sphere.h"


class WorldTree;
class WorldTreeGeode;
class WorldObject;


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
    const WorldTreeGeode* geode() const;
    void setGeode(WorldTreeGeode* geode);

    void setWorldTree(WorldTree* worldTree);
    WorldTree* worldTree();
    const WorldTree* worldTree() const;

    VoxelTree& voxelTree();
    const VoxelTree& voxelTree() const;

    void updateGeode();

    void rebuildVoxelTree();


protected:
    WorldObject& m_worldObject;
    VoxelTree m_voxelTree;
    WorldTreeGeode* m_geode;
    WorldTree* m_worldTree;
    std::list<VoxelCollision> m_collisions;

    void checkCollisions(VoxelTreeNode* nodeA, VoxelTreeNode* nodeB);
    const Sphere& getOrCreateSphere(VoxelTreeNode* node);
};

