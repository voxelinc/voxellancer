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
    m_worldObject(worldObject),
    m_aabb()
{
}

CollisionDetector::~CollisionDetector() {
}

AABB CollisionDetector::aabb(const WorldTransform& transform) const {
    return AABB::containing(sphere(transform));
}

const IAABB &CollisionDetector::gridAABB() const {
    return m_aabb;
}

Sphere CollisionDetector::sphere(const WorldTransform& transform) const {
    Sphere sphere;
    sphere.setPosition(transform.applyTo(glm::vec3(m_aabb.rub() + m_aabb.llf()) / 2.0f));
    // m_aabb only contains the center of each voxel so add sqrt(2) to add the distance from center to edge
    sphere.setRadius((glm::length(glm::vec3(m_aabb.rub() - m_aabb.llf())) + glm::root_two<float>()) / 2.f * transform.scale());
    return sphere;
}

void CollisionDetector::addVoxel(Voxel* voxel) {
    if(m_worldObject.voxelCount() == 0) {
        m_aabb = IAABB(voxel->gridCell(), voxel->gridCell());
    }
    else {
        m_aabb.extend(voxel->gridCell());
    }
    m_voxelTree.insert(voxel);
    updateGeode();
}

void CollisionDetector::removeVoxel(Voxel* voxel) {
    assert(voxel->voxelTreeNode() != nullptr);
    assert(voxel->voxelTreeNode()->voxel() == voxel);
    assert(voxel->voxelTreeNode()->isAtomic());

    glm::ivec3 gridCell = voxel->gridCell();

    voxel->voxelTreeNode()->remove(gridCell);

    if(gridCell.x == m_aabb.llf().x) {
        shrinkPlus(m_aabb.llf().x, m_aabb.rub().x, m_aabb.llf());
    }
    if(gridCell.x == m_aabb.rub().x) {
        shrinkMinus(m_aabb.rub().x, m_aabb.llf().x, m_aabb.rub());
    }
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
    m_aabb = IAABB();
    for (auto& pair: m_worldObject.voxelMap())
    {
        Voxel* voxel = pair.second;
        addVoxel(voxel);
    }
}

void CollisionDetector::shrinkPlus(int start, int end, const glm::ivec3& plane) {
    for(int x = start; x <= end; x++) {
        for(int z = m_aabb.llf().z; z <= m_aabb.rub().z; z++) {
            for(int y = m_aabb.llf().y; y <= m_aabb.rub().y; y++) {
                if(m_worldObject.voxel(glm::ivec3(x,y,z)) != nullptr) {
                    std::cout << "+voxel at " << x << " " << y << " " << z << std::endl;
                    return;
                }
                else {
                    std::cout << "+no voxel at " << x << " " << y << " " << z << std::endl;
                }
            }
        }
        std::cout << "+Found nothing on plane " << x << std::endl;
        if(m_aabb.rub().x > m_aabb.llf().x) {
            m_aabb.setLlf(plane + glm::ivec3(1, 0, 0));
        }
    }
}

void CollisionDetector::shrinkMinus(int start, int end, const glm::ivec3& plane) {
    for(int x = start; x > end; x--) {
        for(int z = m_aabb.llf().z; z <= m_aabb.rub().z; z++) {
            for(int y = m_aabb.llf().y; y <= m_aabb.rub().y; y++) {
                if(m_worldObject.voxel(glm::ivec3(x,y,z)) != nullptr) {
                    return;
                }
                else {
                    std::cout << "no voxel at " << x << " " << y << " " << z << std::endl;
                }
            }
        }
        std::cout << "Found nothing on plane " << x << std::endl;
        if(m_aabb.rub().x > m_aabb.llf().x) {
            m_aabb.setRub(plane + glm::ivec3(-1, 0, 0));
        }
    }
}

