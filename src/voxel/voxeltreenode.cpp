#include "voxeltreenode.h"

#include <cassert>
#include <iostream>

#include "utils/tostring.h"
#include "world/worldobject.h"


VoxeltreeNode::VoxeltreeNode(VoxeltreeNode *parent, CollidableVoxelCluster &voxelcluster, const Grid3dAABB &gridAABB) :
    m_parent(parent),
    m_voxelcluster(voxelcluster),
    m_gridAABB(gridAABB),
    m_voxel(nullptr)
{

}

VoxeltreeNode::VoxeltreeNode(const VoxeltreeNode& other, CollidableVoxelCluster *voxelcluster) :
	m_parent(other.m_parent),
	m_voxelcluster(*voxelcluster),
	m_gridAABB(other.m_gridAABB),
	m_voxel(other.m_voxel),
	m_subnodes()
{
	for (VoxeltreeNode *subnode : other.m_subnodes) {
		m_subnodes.push_back(new VoxeltreeNode(*subnode, voxelcluster));
	}
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

const Grid3dAABB &VoxeltreeNode::gridAABB() const {
    return m_gridAABB;
}

Sphere VoxeltreeNode::boundingSphere() {
    Sphere sphere;
    glm::vec3 center;

    center = static_cast<glm::vec3>(m_gridAABB.rub() + m_gridAABB.llf()) / 2.0f;

    sphere.setPosition(m_voxelcluster.transform().applyTo(center));

    if(m_voxel != nullptr) {
        sphere.setRadius(0.5f * m_voxelcluster.transform().scale());
    }
    else {
        sphere.setRadius(glm::length(glm::vec3(m_gridAABB.rub() - m_gridAABB.llf())/2.0f));
    }

    return sphere;
}

void VoxeltreeNode::insert(Voxel *voxel) {
    if(!m_gridAABB.contains(glm::ivec3(voxel->gridCell()))) {
        octuple();
        insert(voxel);
        return;
    }

    if(isAtomic()) {
        assert(m_voxel == nullptr);
        m_voxel = voxel;
    }
    else {
        if(isLeaf()) {
            split();
        }

        for(VoxeltreeNode *subnode : m_subnodes) {
            if(subnode->gridAABB().contains(glm::ivec3(voxel->gridCell()))) {
                subnode->insert(voxel);
            }
        }
    }
}

void VoxeltreeNode::remove(const cvec3 &cell) {
    if(isAtomic()) {
        assert(m_voxel != nullptr);
        delete m_voxel;
        m_voxel = nullptr;
    }
    else {
        int numSubLeaves = 0;

        for(VoxeltreeNode *subnode : m_subnodes) {
            if(subnode->gridAABB().contains(glm::ivec3(cell))) {
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
    std::list<Grid3dAABB> subnodeAABBs = m_gridAABB.recursiveSplit(2, XAxis);

    for(Grid3dAABB &subAABB : subnodeAABBs) {
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
        Grid3dAABB aabb = m_gridAABB;
        aabb.move(XAxis, sn % 2 >= 1 ? aabb.extent(XAxis) : 0);
        aabb.move(YAxis, sn % 4 >= 2 ? aabb.extent(YAxis) : 0);
        aabb.move(ZAxis, sn % 8 >= 4 ? aabb.extent(ZAxis) : 0);

        m_subnodes.push_back(new VoxeltreeNode(this, m_voxelcluster, aabb));
    }

    m_gridAABB = Grid3dAABB(glm::ivec3(0, 0, 0), (m_gridAABB.rub()+glm::ivec3(1,1,1)) * 2 - glm::ivec3(1,1,1));
}

