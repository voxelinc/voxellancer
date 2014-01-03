#include "voxeltreequery.h"

#include <functional>

#include "voxel/voxel.h"
#include "voxel/voxeltreenode.h"
#include "utils/tostring.h"


VoxelTreeQuery::VoxelTreeQuery(VoxelTreeNode* voxelTree, const AbstractShape* shape):
    m_voxelTree(voxelTree),
    m_shape(shape),
    m_queryInterrupted(false)
{

}

bool VoxelTreeQuery::areVoxelsIntersecting() {
    bool result = false;
    m_queryInterrupted = false;

    query(m_voxelTree, [&](Voxel* voxel) {
        result = true;
        m_queryInterrupted = true;
    });

    return result;
}

std::set<Voxel*> VoxelTreeQuery::intersectingVoxels() {
    std::set<Voxel*> result;
    m_queryInterrupted = false;

    query(m_voxelTree, [&](Voxel* voxel) {
        result.insert(voxel);
    });

    return result;
}

void VoxelTreeQuery::query(VoxelTreeNode* node, std::function<void(Voxel*)> onVoxelIntersection) {
    if (node->isLeaf()) {
        if(node->isVoxel() && m_shape->intersects(node->sphere())) {
            onVoxelIntersection(node->voxel());

            if(m_queryInterrupted) {
                return;
            }
        }
    } else {
        for (VoxelTreeNode* subnode : node->subnodes()) {
            if (m_shape->intersects(subnode->sphere())) {
                query(subnode, onVoxelIntersection);

                if(m_queryInterrupted) {
                    return;
                }
            }
        }
    }
}
