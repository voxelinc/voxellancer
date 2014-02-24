#include "voxeltreequery.h"

#include <functional>

#include "voxel/voxel.h"
#include "voxel/voxeltree.h"
#include "voxel/voxeltreenode.h"
#include "utils/tostring.h"

#include "worldobject/worldobject.h"
#include "geometry/transform.h"

VoxelTreeQuery::VoxelTreeQuery(const WorldObject* worldObject, IVoxelTree* voxelTree, const AbstractShape* shape):
    m_worldObject(worldObject),
    m_voxelTree(voxelTree),
    m_shape(shape),
    m_queryInterrupted(false)
{

}

bool VoxelTreeQuery::areVoxelsIntersecting() {
    bool result = false;
    m_queryInterrupted = false;

    query(m_voxelTree->root(), [&](Voxel* voxel) {
        result = true;
        m_queryInterrupted = true;
    });

    return result;
}

std::unordered_set<Voxel*> VoxelTreeQuery::intersectingVoxels() {
    std::unordered_set<Voxel*> result;
    m_queryInterrupted = false;

    query(m_voxelTree->root(), [&](Voxel* voxel) {
        result.insert(voxel);
    });

    return result;
}

void VoxelTreeQuery::query(VoxelTreeNode* node, std::function<void(Voxel*)> onVoxelIntersection) {
    if (node->isLeaf()) {
        if(node->isVoxel() && m_shape->intersects(node->sphere(m_worldObject->transform()))) {
            onVoxelIntersection(node->voxel());

            if(m_queryInterrupted) {
                return;
            }
        }
    } else {
        for (VoxelTreeNode* subnode : node->subnodes()) {
            if (m_shape->intersects(subnode->sphere(m_worldObject->transform()))) {
                query(subnode, onVoxelIntersection);

                if(m_queryInterrupted) {
                    return;
                }
            }
        }
    }
}
