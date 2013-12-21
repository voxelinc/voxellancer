#include "collisiondetector.h"

#include "worldtree/worldtree.h"
#include "worldtree/worldtreegeode.h"

#include "utils/tostring.h"
#include "worldobject/worldobject.h"

#include "utils/tostring.h"


CollisionDetector::CollisionDetector(WorldObject & worldObject) :
    m_voxelTree(&worldObject),
    m_worldTree(nullptr),
    m_geode(nullptr),
    m_worldObject(worldObject)
{
}

CollisionDetector::~CollisionDetector() {
}

void CollisionDetector::addVoxel(Voxel* voxel) {
    m_voxelTree.insert(voxel);
}

void CollisionDetector::removeVoxel(Voxel* voxel) {
    assert(voxel->voxelTreeNode() != nullptr);
    assert(voxel->voxelTreeNode()->voxel() == voxel);
    assert(voxel->voxelTreeNode()->isAtomic());

    voxel->voxelTreeNode()->remove(voxel->gridCell());
}

VoxelTreeNode &CollisionDetector::voxeltree() {
    return m_voxelTree;
}

const VoxelTreeNode &CollisionDetector::voxeltree() const {
    return m_voxelTree;
}

WorldTreeGeode *CollisionDetector::geode() {
    return m_geode;
}

const WorldTreeGeode *CollisionDetector::geode() const {
    return m_geode;
}

void CollisionDetector::setGeode(WorldTreeGeode *geode) {
    m_geode = geode;
    updateGeode();
}

void CollisionDetector::setWorldTree(WorldTree* worldTree) {
    m_worldTree = worldTree;
}

WorldTree* CollisionDetector::worldTree() {
    return m_worldTree;
}

const WorldTree* CollisionDetector::worldTree() const {
    return m_worldTree;
}

void CollisionDetector::updateGeode() {
    if(m_geode != nullptr) {
        m_geode->setAABB(m_worldObject.aabb());
    }
}

std::list<VoxelCollision>& CollisionDetector::checkCollisions() {
    assert(m_geode != nullptr);

    m_collisions.clear();

    std::set<WorldTreeGeode*> possibleColliders = m_worldTree->geodesInAABB(m_worldObject.aabb(), m_geode->containingNode(), &m_worldObject);
    possibleColliders.erase(m_geode);

    for (WorldTreeGeode* possibleCollider : possibleColliders) {
        assert(possibleCollider->worldObject() != nullptr);
        WorldObject* other = possibleCollider->worldObject();

        assert(m_worldObject.isCollideableWith(other));
        checkCollisions(&m_voxelTree, &other->collisionDetector().voxeltree());
    }

    return m_collisions;
}


void CollisionDetector::checkCollisions(VoxelTreeNode* nodeA, VoxelTreeNode* nodeB) {
    Sphere sphereA = nodeA->boundingSphere();
    Sphere sphereB = nodeB->boundingSphere();

    if (sphereA.intersects(sphereB)) {
        if (nodeA->isLeaf() && nodeB->isLeaf()) {
            if(nodeA->isVoxel() && nodeB->isVoxel()) {
                m_collisions.push_back(VoxelCollision(VoxelCollisionParticipant(nodeA->worldObject(), nodeA->voxel()), VoxelCollisionParticipant(nodeB->worldObject(), nodeB->voxel())));
            }
        }
        else {
            std::vector<VoxelTreeNode*> subnodes;
            VoxelTreeNode *nodeToSplit;
            VoxelTreeNode *otherNode;

            assert(!nodeA->isLeaf() || !nodeB->isLeaf());

            if(sphereA.radius() < sphereB.radius()) {
                otherNode = nodeA;
                nodeToSplit = nodeB;
            }
            else {
                otherNode = nodeB;
                nodeToSplit = nodeA;
            }

            if(nodeToSplit->isLeaf()) {
                VoxelTreeNode* tmp = nodeToSplit;
                nodeToSplit = otherNode;
                otherNode = tmp;
            }

            for(VoxelTreeNode* subnode : nodeToSplit->subnodes()) {
                if(!subnode->isEmpty()) {
                    checkCollisions(subnode, otherNode);
                }
            }
        }
    }
}

std::list<VoxelCollision>& CollisionDetector::lastCollisions() {
    return m_collisions;
}

void CollisionDetector::reset() {
    m_collisions.clear();
}

void CollisionDetector::rebuildVoxelTree() {
    m_voxelTree = VoxelTreeNode(&m_worldObject);
    for (auto& pair: m_worldObject.voxelMap()) {
        Voxel* voxel = pair.second;
        addVoxel(voxel);
    }
}

