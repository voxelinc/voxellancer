#pragma once

#include <unordered_set>
#include <functional>

class Voxel;
class IVoxelTree;
class VoxelTree;
class VoxelTreeNode;
class AbstractShape;
class WorldObject;

class VoxelTreeQuery {
public:
    VoxelTreeQuery(const WorldObject* worldObject, IVoxelTree* voxelTree, const AbstractShape* shape);

    bool areVoxelsIntersecting();
    std::unordered_set<Voxel*> intersectingVoxels();


protected:
    const WorldObject* m_worldObject;
    IVoxelTree* m_voxelTree;
    const AbstractShape* m_shape;
    bool m_queryInterrupted;

    void query(VoxelTreeNode* node, std::function<void(Voxel*)> onVoxelIntersection);
};

