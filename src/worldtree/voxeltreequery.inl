#pragma once

#include <functional>

#include "voxel/voxel.h"
#include "collision/voxeltreenode.h"


template<typename Shape>
VoxelTreeQuery<Shape>::VoxelTreeQuery(VoxelTreeNode* voxelTree, const Shape& shape):
    m_voxelTree(voxelTree),
    m_shape(shape),
    m_queryInterrupted(false)
{

}

template<typename Shape>
bool VoxelTreeQuery<Shape>::areVoxelsIntersecting() {
    bool result = false;
    m_queryInterrupted = false;

    query(m_voxelTree, [&](Voxel* voxel) {
        result = true;
        m_queryInterrupted = true;
    });

    return result;
}

template<typename Shape>
std::set<Voxel*> VoxelTreeQuery<Shape>::intersectingVoxels() {
    std::set<Voxel*> result;
    m_queryInterrupted = false;

    query(m_voxelTree, [&](Voxel* voxel) {
        result.insert(voxel);
    });

    return result;
}

template<typename Shape>
void VoxelTreeQuery<Shape>::query(VoxelTreeNode* node, std::function<void(Voxel*)> onVoxelIntersection) {
    if(node->isLeaf()) {
        if(node->isVoxel() && m_shape.intersects(node->voxel()->normalizedSphere())) {
            onVoxelIntersection(node->voxel());

            if(m_queryInterrupted) {
                return;
            }
        }
    }
    else {
        for(VoxelTreeNode* subnode : node->subnodes()) {
            if(m_shape.intersects(subnode->boundingSphere())) {
                query(subnode, onVoxelIntersection);

                if(m_queryInterrupted) {
                    return;
                }
            }
        }
    }
}
