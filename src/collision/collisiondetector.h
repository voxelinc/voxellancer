#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "voxel/voxel.h"
#include "collision/voxeltreenode.h"
#include "collision/voxelcollision.h"

class WorldTree;
class WorldTreeGeode;
class WorldObject;


// this class contains datastructures for collision detection
class CollisionDetector
{
public:
    CollisionDetector(WorldObject & worldObject);
    ~CollisionDetector();

    void addVoxel(Voxel *voxel);
    void removeVoxel(Voxel *voxel);

    AABB aabb(const WorldTransform& transform) const;
    void recalculateAABB();

    Sphere sphere(const WorldTransform& transform) const;

    std::list<VoxelCollision> &checkCollisions();
    std::list<VoxelCollision> &lastCollisions();
    void reset();

    WorldTreeGeode *geode();
    const WorldTreeGeode *geode() const;
    void setGeode(WorldTreeGeode *geode);
    void setWorldTree(WorldTree* worldTree);
    WorldTree* worldTree();
    const WorldTree* worldTree() const;

    VoxelTreeNode &voxeltree();
    const VoxelTreeNode &voxeltree() const;

    void updateGeode();

    void rebuildVoxelTree();


protected:
    WorldObject& m_worldObject;
    VoxelTreeNode m_voxelTree;
    WorldTreeGeode *m_geode;
    WorldTree *m_worldTree;
    std::list<VoxelCollision> m_collisions;
    IAABB m_aabb;

    void checkCollisions(VoxelTreeNode* nodeA, VoxelTreeNode* nodeB);
};

