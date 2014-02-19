#include "voxeltreenode.h"

#include <cassert>

#include "utils/tostring.h"

#include "voxel/voxeltree.h"

#include "worldobject/worldobject.h"
#include "voxel.h"


static const int SUBNODE_COUNT = 8;

VoxelTreeNode::VoxelTreeNode(int octIndex, VoxelTree* voxelTree, VoxelTreeNode* parent, const GridAABB& gridAABB) :
    m_octIndex(octIndex),
    m_voxelTree(voxelTree),
    m_parent(parent),
    m_gridAABB(gridAABB),
    m_voxel(nullptr),
    m_active(false)
{
    // Find below an ugly hack until #179 is resolved
    calculateSpherePosition(Transform());
    calculateSphereRadius(Transform());
}

VoxelTreeNode::VoxelTreeNode(VoxelTree* voxelTree, const GridAABB &gridAABB, VoxelTreeNode* initialSubnode):
    VoxelTreeNode(0, voxelTree, nullptr, gridAABB)
{
    toGroup();

    delete m_subnodes[0];
    m_subnodes[0] = initialSubnode;
    initialSubnode->setParent(this);

    if(initialSubnode->active()) {
        subnodeActivated(initialSubnode);
    }
}

VoxelTreeNode::~VoxelTreeNode() {
    for(VoxelTreeNode* subnode : m_subnodes) {
        delete subnode;
    }
}

int VoxelTreeNode::octIndex() const {
    return m_octIndex;
}

bool VoxelTreeNode::isAtomic() const {
    assert(m_gridAABB.extent(XAxis) == m_gridAABB.extent(YAxis) && m_gridAABB.extent(YAxis) == m_gridAABB.extent(ZAxis));
    return m_gridAABB.extent(XAxis) == 1;
}

bool VoxelTreeNode::isVoxel() const {
    assert(m_voxel == nullptr || m_subnodes.empty());
    return m_voxel != nullptr;
}

bool VoxelTreeNode::isLeaf() const{
    return m_subnodes.empty();
}

bool VoxelTreeNode::isEmpty() const{
    return isLeaf() && m_voxel == nullptr;
}

std::list<VoxelTreeNode*>& VoxelTreeNode::subnodes() {
    return m_activeSubnodes;
}

const std::list<VoxelTreeNode*>& VoxelTreeNode::subnodes() const {
    return m_activeSubnodes;
}

Voxel* VoxelTreeNode::voxel() {
    return m_voxel;
}

const Voxel* VoxelTreeNode::voxel() const {
    return m_voxel;
}

VoxelTree* VoxelTreeNode::voxelTree() {
    return m_voxelTree;
}

VoxelTreeNode* VoxelTreeNode::parent() {
    return m_parent;
}

void VoxelTreeNode::setParent(VoxelTreeNode* parent) {
    assert(m_parent == nullptr);
    m_parent = parent;
}

const GridAABB& VoxelTreeNode::gridAABB() const {
    return m_gridAABB;
}

Sphere& VoxelTreeNode::sphere() {
    assert(m_voxelTree->worldObject());
    return sphere(m_voxelTree->worldObject()->transform());
}

Sphere& VoxelTreeNode::sphere(const Transform& transform) {
    if (transform.position() != m_cachedSphereTransform.position() ||
        transform.orientation() != m_cachedSphereTransform.orientation() ||
        transform.center() != m_cachedSphereTransform.center() ) {
        calculateSpherePosition(transform);
    }

    if (transform.scale() != m_cachedSphereTransform.scale()) {
        calculateSphereRadius(transform);
    }

    return m_sphere;
}

bool VoxelTreeNode::active() const {
    return m_active;
}

void VoxelTreeNode::setActive(bool active) {
    if (active != m_active) {
        m_active = active;

        if (m_parent != nullptr) {
            if(m_active) {
                m_parent->subnodeActivated(this);
            } else {
                m_parent->subnodeDeactivated(this);
            }
        }
    }
}

void VoxelTreeNode::insert(Voxel* voxel) {
    assert(m_gridAABB.contains(voxel->gridCell()));

    if (isAtomic()) {
        assert(m_voxel == nullptr);

        m_voxel = voxel;
        m_voxel->setVoxelTreeNode(this);

        setActive(true);
    } else {
        if (isLeaf()) {
            toGroup();
        }

        cellSubnode(voxel->gridCell())->insert(voxel);
    }
}

void VoxelTreeNode::remove(Voxel* voxel) {
    if (isAtomic()) {
        assert(m_voxel != nullptr);

        m_voxel->setVoxelTreeNode(nullptr);
        m_voxel = nullptr;

        setActive(false);
    } else {
        cellSubnode(voxel->gridCell())->remove(voxel);
    }
}

void VoxelTreeNode::toGroup() {
    assert(isLeaf());

    int subnodeExtent = m_gridAABB.extent(XAxis) / 2;
    assert(subnodeExtent >= 1);

    m_subnodes.resize(SUBNODE_COUNT);

    for(int n = 0; n < SUBNODE_COUNT; n++) {
        glm::ivec3 llf = glm::ivec3(n % 2, n/2 % 2, n/4) * subnodeExtent + m_gridAABB.llf();
        GridAABB subnodeGridAABB(llf, llf + glm::ivec3(subnodeExtent - 1));

        m_subnodes[n] = new VoxelTreeNode(n, m_voxelTree, this, subnodeGridAABB);
    }

    assert(!isLeaf());
}

void VoxelTreeNode::subnodeActivated(VoxelTreeNode* subnode) {
    m_activeSubnodes.push_back(subnode);
    setActive(true);
}

void VoxelTreeNode::subnodeDeactivated(VoxelTreeNode* subnode) {
    m_activeSubnodes.remove(subnode);

    if(m_activeSubnodes.empty()) {
        setActive(false);
    }
}

VoxelTreeNode* VoxelTreeNode::cellSubnode(const glm::ivec3& cell) {
    assert(!isLeaf());
    glm::ivec3 subnode = (cell - m_gridAABB.llf()) / (m_gridAABB.extent(XAxis) / 2);
    int index = subnode.x + subnode.y * 2 + subnode.z * 4;
    assert(index < SUBNODE_COUNT && index >= 0);

    return m_subnodes[index];
}

void VoxelTreeNode::calculateSpherePosition(const Transform& transform) {
    glm::vec3 center = static_cast<glm::vec3>(m_gridAABB.rub() + m_gridAABB.llf()) / 2.0f;
    m_sphere.setPosition(transform.applyTo(center));

    m_cachedSphereTransform.setPosition(transform.position());
    m_cachedSphereTransform.setCenter(transform.center());
    m_cachedSphereTransform.setOrientation(transform.orientation());
}

void VoxelTreeNode::calculateSphereRadius(const Transform& transform) {
    if(isAtomic()) {
        m_sphere.setRadius(0.5f * transform.scale());
    } else {
        m_sphere.setRadius((glm::length(glm::vec3(m_gridAABB.rub() - m_gridAABB.llf() + glm::ivec3(1, 1, 1))/2.0f)) * transform.scale()) ;
    }

    m_cachedSphereTransform.setScale(transform.scale());
}

