#pragma once

#include <unordered_set>
#include <functional>

class Voxel;
class VoxelTree;
class VoxelTreeNode;
class AbstractShape;

class VoxelTreeQuery {
public:
    VoxelTreeQuery(VoxelTree* voxelTree, const AbstractShape* shape);

    bool areVoxelsIntersecting();
    std::unordered_set<Voxel*> intersectingVoxels();


protected:
    VoxelTree* m_voxelTree;
    const AbstractShape* m_shape;
    bool m_queryInterrupted;

    void query(VoxelTreeNode* node, std::function<void(Voxel*)> onVoxelIntersection);
};

