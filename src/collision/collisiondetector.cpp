#include "collisiondetector.h"

#include <set>
#include <list>
#include <iostream>

#include "utils/tostring.h"
#include "worldobject/worldobject.h"

CollisionDetector::CollisionDetector(WorldTree &worldTree, CollidableVoxelCluster &voxelcluster) :
m_worldTree(worldTree),
m_voxelcluster(voxelcluster),
m_otherVoxelCluster(nullptr)
{

}

CollisionDetector::~CollisionDetector() {

}

std::list<Collision> &CollisionDetector::checkCollisions() {
    assert(m_voxelcluster.geode() != nullptr);

    m_collisions.clear();

    std::set<WorldTreeGeode*> possibleColliders = m_worldTree.geodesInAABB(m_voxelcluster.geode()->aabb(), m_voxelcluster.geode()->containingNode());
    possibleColliders.erase(m_voxelcluster.geode());

    for(WorldTreeGeode *possibleCollider : possibleColliders) {
        assert(possibleCollider->voxelcluster() != nullptr);
        m_otherVoxelCluster = possibleCollider->voxelcluster();
        checkCollisions(&m_voxelcluster.voxeltree(), &possibleCollider->voxelcluster()->voxeltree());
    }
    m_otherVoxelCluster = nullptr;

    return m_collisions;
}

void CollisionDetector::checkCollisions(VoxelTreeNode* nodeA, VoxelTreeNode* nodeB) {
    if(nodeA->isLeaf() && nodeA->voxel() == nullptr) {
        return;
    }
    if(nodeB->isLeaf() && nodeB->voxel() == nullptr) {
        return;
    }

    if(nodeA->boundingSphere().intersects(nodeB->boundingSphere())) {
        if(nodeA->isLeaf() && nodeB->isLeaf()) {
            if(nodeA->voxel() != nullptr && nodeB->voxel() != nullptr) {
                m_collisions.push_back(Collision(nodeA->voxel(), nodeB->voxel(), &m_voxelcluster, m_otherVoxelCluster));
            }
        }
        else {
            std::vector<VoxelTreeNode*> nodesA, nodesB;

            auto assignList = [] (VoxelTreeNode *node, std::vector<VoxelTreeNode*> &list) {
                if(node->isLeaf()) {
                    list.push_back(node);
                }
                else {
                    list = node->subnodes();
                }
            };

            assignList(nodeA, nodesA);
            assignList(nodeB, nodesB);

            for(VoxelTreeNode *nodeA : nodesA) {
                for(VoxelTreeNode *nodeB : nodesB) {
                    checkCollisions(nodeA, nodeB);
                }
            }
        }
    }
}

std::list<Collision> & CollisionDetector::lastCollisions() {
    return m_collisions;
}

void CollisionDetector::reset() {
    m_collisions.clear();
}


