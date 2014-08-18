#include "collisiondetector.h"

#include "voxel/voxeltreenode.h"

#include "worldtree/worldtree.h"
#include "worldtree/worldtreegeode.h"
#include "worldtree/worldtreequery.h"

#include "worldobject/worldobject.h"
#include "geometry/sphere.h"
#include "voxel/voxeltree.h"
#include "collisionfilter.h"
#include "voxel/voxelclusterbounds.h"


CollisionDetector::CollisionDetector(WorldObject& worldObject):
    m_voxelTree(new VoxelTree(&worldObject)),
    m_worldTree(nullptr),
    m_geode(nullptr),
    m_worldObject(worldObject)
{
}

CollisionDetector::~CollisionDetector() = default;

void CollisionDetector::addVoxel(Voxel* voxel) {
    m_voxelTree->insert(voxel);
}

void CollisionDetector::removeVoxel(Voxel* voxel) {
    m_voxelTree->remove(voxel);
}

VoxelTree& CollisionDetector::voxelTree() {
    return *m_voxelTree;
}

WorldTreeGeode *CollisionDetector::geode() {
    return m_geode;
}

void CollisionDetector::setGeode(WorldTreeGeode *geode) {
    m_geode = geode;
}

void CollisionDetector::setWorldTree(WorldTree* worldTree) {
    m_worldTree = worldTree;
}

WorldTree* CollisionDetector::worldTree() {
    return m_worldTree;
}

void CollisionDetector::updateGeode() {
    if(m_geode != nullptr) {
        assert(m_worldTree);

        m_geode->setAABB(m_worldObject.bounds().aabb());
        m_worldTree->aabbChanged(m_geode);
    }
}

std::list<VoxelCollision>& CollisionDetector::checkCollisions() {
    assert(m_geode != nullptr);

    m_collisions.clear();

    IAABB worldObjectAABB = m_worldObject.bounds().aabb();
    std::unordered_set<WorldTreeGeode*> possibleColliders = WorldTreeQuery(m_worldTree, &worldObjectAABB, m_geode->hint(), &m_worldObject.collisionFilter()).nearGeodes();

    checkCollisions(possibleColliders);

    return m_collisions;
}


std::list<VoxelCollision>& CollisionDetector::checkCollisions(const std::unordered_set<WorldTreeGeode*>& possibleColliders) {
    for (WorldTreeGeode* possibleCollider : possibleColliders) {
        assert(possibleCollider->worldObject() != nullptr);
        WorldObject* other = possibleCollider->worldObject();

        assert(m_worldObject.collisionFilter().isCollideableWith(&other->collisionFilter()));
        checkCollisions(m_voxelTree->root(), other->collisionDetector().voxelTree().root());
    }

    return m_collisions;
}

std::list<VoxelCollision>& CollisionDetector::lastCollisions() {
    return m_collisions;
}

void CollisionDetector::reset() {
    m_collisions.clear();
}

void CollisionDetector::checkCollisions(VoxelTreeNode* nodeA, VoxelTreeNode* nodeB) {
    const Sphere& sphereA = nodeA->sphere();
    const Sphere& sphereB = nodeB->sphere();

    if (sphereA.intersects(sphereB)) {
        if (nodeA->isLeaf() && nodeB->isLeaf()) {
            if (nodeA->isVoxel() && nodeB->isVoxel()) {
                m_collisions.push_back(VoxelCollision(VoxelCollisionParticipant(nodeA->voxelTree()->worldObject(), nodeA->voxel()), VoxelCollisionParticipant(nodeB->voxelTree()->worldObject(), nodeB->voxel())));
            }
        } else {
            VoxelTreeNode *nodeToSplit;
            VoxelTreeNode *otherNode;

            assert(!nodeA->isLeaf() || !nodeB->isLeaf());

            if (sphereA.radius() < sphereB.radius()) {
                otherNode = nodeA;
                nodeToSplit = nodeB;
            } else {
                otherNode = nodeB;
                nodeToSplit = nodeA;
            }

            if (nodeToSplit->isLeaf()) {
                std::swap(nodeToSplit, otherNode);
            }

            for (VoxelTreeNode* subnode : nodeToSplit->subnodes()) {
                checkCollisions(subnode, otherNode);
            }
        }
    }
}

