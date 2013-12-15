#include "voxeltreenode.h"

#include <cassert>

#include "utils/tostring.h"
#include "worldobject/worldobject.h"


VoxelTreeNode::VoxelTreeNode(WorldObject *worldObject, VoxelTreeNode *parent, const Grid3dAABB &gridAABB) :
    m_parent(parent),
    m_worldObject(worldObject),
    m_gridAABB(gridAABB),
    m_voxel(nullptr),
    m_boundingSphereRadiusValid(false)
{

}

VoxelTreeNode::~VoxelTreeNode() {
    for(VoxelTreeNode *subnode : m_subnodes) {
        delete subnode;
    }
}

bool VoxelTreeNode::isAtomic() const {
    assert(m_gridAABB.extent(XAxis) == m_gridAABB.extent(YAxis) && m_gridAABB.extent(YAxis) == m_gridAABB.extent(ZAxis));
    return m_gridAABB.extent(XAxis) == 1;
}

bool VoxelTreeNode::isVoxel() const {
    assert((m_voxel != nullptr) ? m_subnodes.empty() : 1);
    return m_voxel != nullptr;
}

bool VoxelTreeNode::isLeaf() const{
    return m_subnodes.empty();
}

bool VoxelTreeNode::isEmpty() const{
    return isLeaf() && m_voxel == nullptr;
}

std::vector<VoxelTreeNode*> &VoxelTreeNode::subnodes() {
    return m_subnodes;
}

const std::vector<VoxelTreeNode*> &VoxelTreeNode::subnodes() const {
    return m_subnodes;
}

Voxel *VoxelTreeNode::voxel(){
    return m_voxel;
}

const Voxel *VoxelTreeNode::voxel() const{
    return m_voxel;
}

WorldObject* VoxelTreeNode::worldObject() {
    return m_worldObject;
}

const Grid3dAABB &VoxelTreeNode::gridAABB() const {
    return m_gridAABB;
}

Sphere VoxelTreeNode::boundingSphere() {
    glm::vec3 center;

    center = static_cast<glm::vec3>(m_gridAABB.rub() + m_gridAABB.llf()) / 2.0f;

    m_boundingSphere.setPosition(m_worldObject->transform().applyTo(center));

    if (!m_boundingSphereRadiusValid) {
        if(m_voxel != nullptr) {
            m_boundingSphere.setRadius(0.5f * m_worldObject->transform().scale());
        }
        else {
            m_boundingSphere.setRadius((glm::length(glm::vec3(m_gridAABB.rub() - m_gridAABB.llf() + glm::ivec3(1, 1, 1))/2.0f)) * m_worldObject->transform().scale()) ;
        }
        m_boundingSphereRadiusValid = true;
    }

    return m_boundingSphere;
}

void VoxelTreeNode::insert(Voxel* voxel) {
    if(!m_gridAABB.contains(glm::ivec3(voxel->gridCell()))) {
        octuple();
        insert(voxel);
        return;
    }

    if(isAtomic()) {
        assert(m_voxel == nullptr);

        m_voxel = voxel;
        m_voxel->setVoxelTreeNode(this);
        m_boundingSphereRadiusValid = false;
    }
    else {
        if(isLeaf()) {
            split();
        }

        for(VoxelTreeNode *subnode : m_subnodes) {
            if(subnode->gridAABB().contains(glm::ivec3(voxel->gridCell()))) {
                subnode->insert(voxel);
            }
        }
    }
}

void VoxelTreeNode::remove(const glm::ivec3 &cell) {
    if(isAtomic()) {
        assert(m_voxel != nullptr);

        m_voxel->setVoxelTreeNode(nullptr);
        m_voxel = nullptr;
        m_boundingSphereRadiusValid = false;
    }
    else {
        int numSubNodesEmpty = 0;

        for(VoxelTreeNode *subnode : m_subnodes) {
            if(subnode->gridAABB().contains(cell)) {
                subnode->remove(cell);
            }
            if(subnode->isEmpty()) {
                numSubNodesEmpty++;
            }
        }

        if(numSubNodesEmpty == 8) {
            unsplit();
        }
    }
}

void VoxelTreeNode::split() {
    std::list<Grid3dAABB> subnodeAABBs = m_gridAABB.recursiveSplit(2, XAxis);

    for(Grid3dAABB &subAABB : subnodeAABBs) {
        m_subnodes.push_back(new VoxelTreeNode(m_worldObject, this, subAABB));
    }
}

void VoxelTreeNode::unsplit() {
    assert(m_subnodes.size() == 8);
    for(VoxelTreeNode *subnode : m_subnodes) {
        delete subnode;
    }
    m_subnodes.clear();
}

void VoxelTreeNode::octuple() {
    VoxelTreeNode *thisCopy = new VoxelTreeNode(m_worldObject, this, m_gridAABB);

    thisCopy->m_subnodes = m_subnodes;
    thisCopy->m_voxel = m_voxel;

    m_subnodes.clear();
    m_voxel = nullptr;

    m_subnodes.push_back(thisCopy);

    for(int sn = 1; sn < 8; sn++) {
        Grid3dAABB aabb = m_gridAABB;
        aabb.move(XAxis, sn % 2 >= 1 ? aabb.extent(XAxis) : 0);
        aabb.move(YAxis, sn % 4 >= 2 ? aabb.extent(YAxis) : 0);
        aabb.move(ZAxis, sn % 8 >= 4 ? aabb.extent(ZAxis) : 0);

        m_subnodes.push_back(new VoxelTreeNode(m_worldObject, this, aabb));
    }

    m_gridAABB = Grid3dAABB(glm::ivec3(0, 0, 0), (m_gridAABB.rub()+glm::ivec3(1,1,1)) * 2 - glm::ivec3(1,1,1));
    m_boundingSphereRadiusValid = false;
}

