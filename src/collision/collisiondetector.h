#pragma once 

#include <memory>

#include <glm/glm.hpp>

#include "voxel/voxel.h"
#include "voxel/voxeltreenode.h"
#include "collision/collision.h"

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
    void removeVoxel(const glm::ivec3 &position);

    AABB aabb(const WorldTransform& transform);
    Sphere sphere(const WorldTransform& transform);

    std::list<Collision> &checkCollisions();
    std::list<Collision> &lastCollisions();
    void reset();

    WorldTreeGeode *geode();
    const WorldTreeGeode *geode() const;
    void setGeode(WorldTreeGeode *geode);
    void setWorldTree(WorldTree* worldTree);
    WorldTree* worldTree();

    VoxelTreeNode &voxeltree();
    const VoxelTreeNode &voxeltree() const;

    void updateGeode();
        
    void finishInitialization();


protected:
    void checkCollisions(VoxelTreeNode* nodeA, VoxelTreeNode* nodeB, WorldObject *  other);

    WorldObject & m_worldObject;
    VoxelTreeNode m_voxelTree;
    WorldTreeGeode *m_geode;
    WorldTree *m_worldTree;
    std::list<Collision> m_collisions;
    IAABB m_aabb;

};
