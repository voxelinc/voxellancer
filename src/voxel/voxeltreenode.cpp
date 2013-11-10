#include "voxeltreenode.h"

#include <cassert>

#include "voxel/voxelcluster.h"


VoxeltreeNode::VoxeltreeNode(VoxeltreeNode *parent, VoxelCluster &voxelcluster, const IAABB &gridAABB):
    m_parent(parent),
    m_voxelcluster(voxelcluster),
    m_gridAABB(gridAABB),
    m_voxel(nullptr)
{
    m_centerRelPosition = static_cast<glm::vec3>(m_gridAABB.llf()) + static_cast<glm::vec3>(m_gridAABB.rub() - m_gridAABB.llf()) / 2.0f;
    m_centerRelPosition -= m_voxelcluster.center();
}

VoxeltreeNode::~VoxeltreeNode() {
    for(VoxeltreeNode *subnode : m_subnodes) {
        delete subnode;
    }
}

bool VoxeltreeNode::isAtomic() const {
    assert(m_gridAABB.extent(XAxis) == m_gridAABB.extent(YAxis) && m_gridAABB.extent(YAxis) == m_gridAABB.extent(ZAxis));
    return m_gridAABB.extent(XAxis) == 1;
}

bool VoxeltreeNode::isLeaf() const{
    return m_subnodes.size() == 0;
}

std::vector<VoxeltreeNode*> &VoxeltreeNode::subnodes() {
    return m_subnodes;
}

const std::vector<VoxeltreeNode*> &VoxeltreeNode::subnodes() const {
    return m_subnodes;
}

Voxel *VoxeltreeNode::voxel(){
    return m_voxel;
}

const Voxel *VoxeltreeNode::voxel() const{
    return m_voxel;
}

const IAABB &VoxeltreeNode::gridAABB() const {
    return m_gridAABB;
}

const Sphere &VoxeltreeNode::boundingSphere() {
    if(m_parent != nullptr) {
        m_parent->applyTransformCache();
    }

    return m_boundingSphere;
}

void VoxeltreeNode::insert(Voxel *voxel) {
    if(!m_gridAABB.contains(voxel->gridCell())) {
        octuple();
        insert(voxel);
        return;
    }

    if(isAtomic()) {
        assert(m_voxel == nullptr);
        m_voxel = voxel;
    }
    else {
        split();

        for(VoxeltreeNode *subnode : m_subnodes) {
            if(subnode->gridAABB().contains(voxel->gridCell())) {
                subnode->insert(voxel);
            }
        }
    }
}

void VoxeltreeNode::remove(const glm::ivec3 &cell) {
    if(isAtomic()) {
        assert(m_voxel != nullptr);
        delete m_voxel;
        m_voxel = nullptr;
    }
    else {
        int numSubLeaves = 0;

        for(VoxeltreeNode *subnode : m_subnodes) {
            if(subnode->gridAABB().contains(cell)) {
                subnode->remove(cell);
            }
            if(subnode->isLeaf()) {
                numSubLeaves++;
            }
        }

        if(numSubLeaves == 8) {
            unsplit();
        }
    }
}

void VoxeltreeNode::split() {
    std::list<IAABB> subnodeAABBs = m_gridAABB.recursiveSplit(2, XAxis);

    for(IAABB &subAABB : subnodeAABBs) {
        m_subnodes.push_back(new VoxeltreeNode(this, m_voxelcluster, subAABB));
    }
}

void VoxeltreeNode::unsplit() {
    assert(m_subnodes.size() == 8);
    for(VoxeltreeNode *subnode : m_subnodes) {
        delete subnode;
    }
    m_subnodes.clear();
}

void VoxeltreeNode::octuple() {
    VoxeltreeNode *thisCopy = new VoxeltreeNode(this, m_voxelcluster, m_gridAABB);

    thisCopy->m_subnodes = m_subnodes;
    thisCopy->m_voxel = m_voxel;

    m_subnodes.clear();
    m_voxel = nullptr;

    m_subnodes.push_back(thisCopy);

    for(int sn = 1; sn < 8; sn++) {
        IAABB aabb = m_gridAABB;
        aabb.move(XAxis, sn % 2 >= 1 ? aabb.extent(XAxis) : 0);
        aabb.move(YAxis, sn % 4 >= 2 ? aabb.extent(YAxis) : 0);
        aabb.move(ZAxis, sn % 8 >= 4 ? aabb.extent(ZAxis) : 0);

        m_subnodes.push_back(new VoxeltreeNode(this, m_voxelcluster, aabb));
    }

    m_gridAABB = IAABB(glm::ivec3(0, 0, 0), m_gridAABB.rub() * 2);
}

void VoxeltreeNode::transform(const WorldTransform &transform) {
    m_transformCache.add(transform);

    glm::vec4 rotatedCenter = glm::vec4(m_centerRelPosition, 1.0f) * glm::mat4_cast(transform.orientation());
    m_boundingSphere.setPosition(glm::vec3(rotatedCenter) + m_voxelcluster.position());
}

void VoxeltreeNode::applyTransformCache() {
    for(VoxeltreeNode *subnode : m_subnodes) {
        subnode->transform(m_transformCache);
    }
    m_transformCache.clear();
}
