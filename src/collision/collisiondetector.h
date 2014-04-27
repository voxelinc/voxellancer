#pragma once

#include <memory>
#include <list>
#include <unordered_set>

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
class CollisionDetector {
public:
    CollisionDetector(WorldObject& worldObject);
    ~CollisionDetector();

    void addVoxel(Voxel* voxel);
    void removeVoxel(Voxel* voxel);

    /**
     * Checks for collision against all objects inside worldObject->aabb() that
     * match worldObeject->collisionFilter()
     */
    std::list<VoxelCollision>& checkCollisions();

    /**
     * Check for collision against a caller-defined set of WorldObjects
     */
    std::list<VoxelCollision>& checkCollisions(const std::unordered_set<WorldTreeGeode*>& possibleColliders);

    std::list<VoxelCollision>& lastCollisions();

    void reset();

    WorldTreeGeode* geode();
    void setGeode(WorldTreeGeode* geode);

    void setWorldTree(WorldTree* worldTree);
    WorldTree* worldTree();

    VoxelTree& voxelTree();

    void updateGeode();


protected:
    std::unique_ptr<VoxelTree> m_voxelTree;
    WorldObject& m_worldObject;
    WorldTreeGeode* m_geode;
    WorldTree* m_worldTree;
    std::list<VoxelCollision> m_collisions;

    void checkCollisions(VoxelTreeNode* nodeA, VoxelTreeNode* nodeB);
    const Sphere& getOrCreateSphere(VoxelTreeNode* node);
};

