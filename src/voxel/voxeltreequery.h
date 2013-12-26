#pragma once

#include <set>
#include <functional>

#include "geometry/abstractshape.h"


class Voxel;
class VoxelTreeNode;

class VoxelTreeQuery {
public:
    VoxelTreeQuery(VoxelTreeNode* voxelTree, const AbstractShape* shape);

    bool areVoxelsIntersecting();
    std::set<Voxel*> intersectingVoxels();


protected:
    VoxelTreeNode* m_voxelTree;
    const AbstractShape* m_shape;
    bool m_queryInterrupted;

    void query(VoxelTreeNode* node, std::function<void(Voxel*)> onVoxelIntersection);
};


