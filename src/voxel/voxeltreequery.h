#pragma once

#include <set>


class Voxel;
class VoxelTreeNode;

template<typename Shape>
class VoxelTreeQuery {
public:
    VoxelTreeQuery(VoxelTreeNode* voxelTree, const Shape& shape);

    bool areVoxelsIntersecting();
    std::set<Voxel*> intersectingVoxels();


protected:
    VoxelTreeNode* m_voxelTree;
    Shape m_shape;
    bool m_queryInterrupted;

    void query(VoxelTreeNode* node, std::function<void(Voxel*)> onVoxelIntersection);
};


#include "voxeltreequery.inl"

