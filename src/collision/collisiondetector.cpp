
#include "worldtree/worldtree.h"
#include "worldtree/worldtreegeode.h"
#include "collision/collisiondetector.h"
#include "world/worldobject.h"
#include <iostream>


CollisionDetector::CollisionDetector(WorldObject & worldObject) :
    m_voxelTree(nullptr, worldObject, Grid3dAABB(glm::ivec3(0, 0, 0), glm::ivec3(0, 0, 0))),
    m_worldTree(nullptr),
    m_geode(nullptr),
    m_worldObject(worldObject),
    m_aabb()
{
}

CollisionDetector::~CollisionDetector() {
}

AABB CollisionDetector::aabb(const WorldTransform& transform) {
    return AABB::containing(sphere(transform));
}

Sphere CollisionDetector::sphere(const WorldTransform& transform) {
    Sphere sphere;
    sphere.setPosition(transform.applyTo(glm::vec3(m_aabb.rub() + m_aabb.llf()) / 2.0f));
    // m_aabb only contains the center of each voxel so add sqrt(2) to add the distance from center to edge
    sphere.setRadius((glm::length(glm::vec3(m_aabb.rub() - m_aabb.llf())) + glm::root_two<float>()) / 2.f * transform.scale());
    return sphere;
}

void CollisionDetector::addVoxel(Voxel *voxel) {
    m_aabb.extend(voxel->gridCell());
    m_voxelTree.insert(voxel);
}

void CollisionDetector::removeVoxel(const glm::ivec3 & position) {
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

void CollisionDetector::updateGeode() {
    if(m_geode != nullptr) {
        m_geode->setAABB(m_worldObject.aabb());
    }
    else {
        std::cout << "no geode set" << std::endl;
    }
}

std::list<Collision> &CollisionDetector::checkCollisions() {
    assert(m_geode != nullptr);

    m_collisions.clear();

    std::set<WorldTreeGeode*> possibleColliders = m_worldTree->geodesInAABB(m_worldObject.aabb(), m_geode->containingNode());
    possibleColliders.erase(m_geode);

    for (WorldTreeGeode *possibleCollider : possibleColliders) {
        assert(possibleCollider->worldObject() != nullptr);
        WorldObject * other = possibleCollider->worldObject();
        checkCollisions(&m_voxelTree, &other->collisionDetector().voxeltree(), other);
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


