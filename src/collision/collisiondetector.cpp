
#include "worldtree/worldtreegeode.h"
#include "collision/collisiondetector.h"
#include "world/worldobject.h"


CollisionDetector::CollisionDetector(WorldObject & worldObject) :
    m_voxelTree(nullptr, &worldObject, Grid3dAABB(glm::ivec3(0, 0, 0), glm::ivec3(0, 0, 0))),
    m_worldTree(nullptr),
    m_geode(nullptr),
    m_worldObject(worldObject)
{
}

CollisionDetector::~CollisionDetector() {
}

void CollisionDetector::addVoxel(Voxel *voxel) {
    m_voxelTree.insert(voxel);
}

void CollisionDetector::removeVoxel(const cvec3 & position) {
    m_voxelTree.remove(position);
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

WorldTree* CollisionDetector::worldTree(){
    return m_worldTree;
}

void CollisionDetector::finishInitialization() {
    m_worldTree.updateGeode();
}

std::list<Collision> &CollisionDetector::checkCollisions() {
    assert(m_voxelcluster.geode() != nullptr);

    m_collisions.clear();

    std::set<WorldTreeGeode*> possibleColliders = m_worldTree.geodesInAABB(m_voxelcluster.geode()->aabb(), m_voxelcluster.geode()->containingNode());
    possibleColliders.erase(m_voxelcluster.geode());

    for (WorldTreeGeode *possibleCollider : possibleColliders) {
        assert(possibleCollider->worldobject() != nullptr);
        m_otherVoxelCluster = possibleCollider->worldobject();
        checkCollisions(&m_voxelcluster.voxeltree(), &possibleCollider->worldobject()->voxeltree());
    }
    m_otherVoxelCluster = nullptr;

    return m_collisions;
}

void CollisionDetector::checkCollisions(VoxelTreeNode* nodeA, VoxelTreeNode* nodeB) {
    if (nodeA->isLeaf() && nodeA->voxel() == nullptr) {
        return;
    }
    if (nodeB->isLeaf() && nodeB->voxel() == nullptr) {
        return;
    }

    if (nodeA->boundingSphere().intersects(nodeB->boundingSphere())) {
        if (nodeA->isLeaf() && nodeB->isLeaf()) {
            if (nodeA->voxel() != nullptr && nodeB->voxel() != nullptr) {
                m_collisions.push_back(Collision(nodeA->voxel(), nodeB->voxel(), &m_voxelcluster, m_otherVoxelCluster));
            }
        }
        else {
            std::vector<VoxelTreeNode*> nodesA, nodesB;

            auto assignList = [](VoxelTreeNode *node, std::vector<VoxelTreeNode*> &list) {
                if (node->isLeaf()) {
                    list.push_back(node);
                }
                else {
                    list = node->subnodes();
                }
            };

            assignList(nodeA, nodesA);
            assignList(nodeB, nodesB);

            for (VoxelTreeNode *nodeA : nodesA) {
                for (VoxelTreeNode *nodeB : nodesB) {
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


