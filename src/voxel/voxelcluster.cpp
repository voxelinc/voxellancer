#include "voxelcluster.h"

#include <iostream>
#include <list>

#include <glm/gtc/quaternion.hpp>

#include <glow/DebugMessageOutput.h>
#include <glow/ChangeListener.h>
#include <glow/logging.h>
#include <glowutils/MathMacros.h>


#include "utils/tostring.h"
#include "worldtree/worldtreegeode.h"
#include "collision/collisiondetector.h"


VoxelCluster::VoxelCluster(glm::vec3 center, float scale): 
    m_voxel(),
    m_voxelTree(nullptr, *this, Grid3dAABB(glm::ivec3(0, 0, 0), glm::ivec3(0, 0, 0))),
    m_geode(nullptr),
    m_voxelRenderData(this),
    m_transform(center, scale),
    m_oldTransform(center, scale)
{
}

VoxelCluster::~VoxelCluster() {

}

AABB VoxelCluster::aabb() {
    return AABB::containing(m_voxelTree.boundingSphere());
}

WorldTransform &VoxelCluster::transform() {
    return m_transform;
}

const WorldTransform &VoxelCluster::transform() const {
    return m_transform;
}

VoxeltreeNode &VoxelCluster::voxeltree() {
    return m_voxelTree;
}

const VoxeltreeNode &VoxelCluster::voxeltree() const {
    return m_voxelTree;
}

WorldtreeGeode *VoxelCluster::geode() {
    return m_geode;
}

const WorldtreeGeode *VoxelCluster::geode() const {
    return m_geode;
}

void VoxelCluster::setGeode(WorldtreeGeode *geode) {
    m_geode = geode;

    updateGeode();
}

void VoxelCluster::addVoxel(const Voxel & voxel) {
    
    m_voxel[voxel.gridCell()] = voxel;

    m_voxelTree.insert(new Voxel(voxel));

    m_voxelRenderData.invalidate();

    updateGeode();
}

void VoxelCluster::removeVoxel(const cvec3 & position) {
    m_voxel.erase(position);
    m_voxelTree.remove(position);
    m_voxelRenderData.invalidate();
}

const std::unordered_map<cvec3, Voxel, VoxelHash> & VoxelCluster::voxel() const{
    return m_voxel;
}

VoxelRenderData * VoxelCluster::voxelRenderData() {
    return &m_voxelRenderData;
}

void VoxelCluster::updateGeode() {
    if (m_geode != nullptr) {
        m_geode->setAABB(aabb());
    }
}

void VoxelCluster::setWorldTree(Worldtree* worldTree) {
    m_worldTree = worldTree;
}

void VoxelCluster::update(float delta_sec) {

}



