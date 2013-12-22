#include "collisiondetector.h"

#include "worldtree/worldtree.h"
#include "worldtree/worldtreegeode.h"
#include "worldtree/worldtreequery.h"

#include "utils/tostring.h"
#include "worldobject/worldobject.h"

#include "utils/tostring.h"


CollisionDetector::CollisionDetector(WorldObject & worldObject) :
    m_voxelTree(&worldObject),
    m_worldTree(nullptr),
    m_geode(nullptr),
    m_worldObject(worldObject),
    m_aabb()
{
}

CollisionDetector::~CollisionDetector() {
}

AABB CollisionDetector::aabb(const WorldTransform& transform) const {
    return AABB::containing(sphere(transform));
}

void CollisionDetector::recalculateAABB() {
    m_aabb = IAABB(glm::ivec3(0, 0, 0), glm::ivec3(0, 0, 0));
    bool aabbInitialized = false;

    for(const std::pair<const glm::ivec3, Voxel*>& p : m_worldObject.voxelMap()) {
        assert(p.second != nullptr);

        if(!aabbInitialized) {
            m_aabb = IAABB(p.second->gridCell(), p.second->gridCell());
            aabbInitialized = true;
        }
        else {
            m_aabb.extend(p.second->gridCell());
        }
    }

    m_worldTree->aabbChanged(m_geode);
}

Sphere CollisionDetector::sphere(const WorldTransform& transform) const {
    Sphere sphere;
    sphere.setPosition(transform.applyTo(glm::vec3(m_aabb.rub() + m_aabb.llf()) / 2.0f));
    // m_aabb only contains the center of each voxel so add sqrt(2) to add the distance from center to edge
    sphere.setRadius((glm::length(glm::vec3(m_aabb.rub() - m_aabb.llf())) + glm::root_two<float>()) / 2.f * transform.scale());
    return sphere;
}

void CollisionDetector::addVoxel(Voxel *voxel) {
    if(m_worldObject.voxelCount() == 0) {
        m_aabb = IAABB(voxel->gridCell(), voxel->gridCell());
    }
    else {
        m_aabb.extend(voxel->gridCell());
    }
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

std::set<Voxel*> CollisionDetector::voxelsIntersectingSphere(const Sphere& sphere) const {
    WorldTransform transform = m_worldObject.transform();

    Sphere localSphere;
    localSphere.setPosition(transform.inverseApplyTo(sphere.position()));
    localSphere.setRadius(transform.scale() * sphere.radius());

    return m_voxelTree.voxelsIntersectingSphere(localSphere);
}

std::set<Voxel*> CollisionDetector::voxelsIntersectingRay(const Ray& ray) const {
    WorldTransform transform = m_worldObject.transform();

    Ray localRay(transform.inverseApplyTo(ray.origin()), transform.inverseApplyTo(ray.direction()));

    return m_voxelTree.voxelsIntersectingRay(localRay);
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

void CollisionDetector::finishInitialization() {
    updateGeode();
}

void CollisionDetector::updateGeode() {
    if(m_geode != nullptr) {
        m_geode->setAABB(m_worldObject.aabb());
    }
}

std::list<VoxelCollision>& CollisionDetector::checkCollisions() {
    assert(m_geode != nullptr);

    m_collisions.clear();

    std::set<WorldTreeGeode*> possibleColliders = WorldTreeQuery<AABB>(m_worldTree, m_worldObject.aabb(), m_geode->containingNode(), &m_worldObject).intersectingGeodes();
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

std::list<VoxelCollision> & CollisionDetector::lastCollisions() {
    return m_collisions;
}

void CollisionDetector::reset() {
    m_collisions.clear();
}

void CollisionDetector::rebuildVoxelTree() {
    m_voxelTree = VoxelTreeNode(&m_worldObject);
    m_aabb = IAABB();
    for (auto& pair: m_worldObject.voxelMap())
    {
        Voxel* voxel = pair.second;
        addVoxel(voxel);

    }
}


