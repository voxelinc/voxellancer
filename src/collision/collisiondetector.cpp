
#include "worldtree/worldtree.h"
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
    updateGeode();
}

void CollisionDetector::updateGeode()
{
    m_geode->setAABB(m_worldObject.aabb());
}

std::list<Collision> &CollisionDetector::checkCollisions() {
    //assert(m_voxelcluster.geode() != nullptr);

    m_collisions.clear();

    std::set<WorldTreeGeode*> possibleColliders = m_worldTree->geodesInAABB(m_worldObject.aabb(), m_geode->containingNode());
    possibleColliders.erase(m_geode);

    for (WorldTreeGeode *possibleCollider : possibleColliders) {
        assert(possibleCollider->worldobject() != nullptr);
        WorldObject * other = possibleCollider->worldobject();
        checkCollisions(&m_voxelTree, &other->collisionDetector()->voxeltree(), other);
    }

    return m_collisions;
}

void CollisionDetector::checkCollisions(VoxelTreeNode* nodeA, VoxelTreeNode* nodeB, WorldObject *  other) {
    if (nodeA->isLeaf() && nodeA->voxel() == nullptr) {
        return;
    }
    if (nodeB->isLeaf() && nodeB->voxel() == nullptr) {
        return;
    }

    if (nodeA->boundingSphere().intersects(nodeB->boundingSphere())) {
        if (nodeA->isLeaf() && nodeB->isLeaf()) {
            if (nodeA->voxel() != nullptr && nodeB->voxel() != nullptr) {
                m_collisions.push_back(Collision(CollisionParticipant(&m_worldObject, nodeA->voxel(), glm::vec3(0)), CollisionParticipant(other, nodeB->voxel(), glm::vec3(0))));
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
                    checkCollisions(nodeA, nodeB, other);
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


