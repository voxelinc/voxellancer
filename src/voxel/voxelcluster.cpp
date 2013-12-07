#include "voxelcluster.h"

#include <iostream>
#include <list>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <glow/DebugMessageOutput.h>
#include <glow/ChangeListener.h>
#include <glow/logging.h>
#include <glowutils/MathMacros.h>

#include "utils/tostring.h"


VoxelCluster::VoxelCluster(float scale):
    m_voxels(),
    m_voxelRenderData(m_voxels),
    m_transform(glm::vec3(0), scale)
{
}

VoxelCluster::~VoxelCluster() {
    // free all clusters
    for (auto& element : m_voxels){
        delete element.second;
    }
}

Voxel* VoxelCluster::voxel(const glm::ivec3& position) {
    std::unordered_map<glm::ivec3, Voxel*>::iterator i = m_voxels.find(position);
    return i == m_voxels.end() ? nullptr : i->second;
}

void VoxelCluster::addVoxel(Voxel *voxel) {
    assert(m_voxels[voxel->gridCell()] == nullptr);
    
    m_voxels[voxel->gridCell()] = voxel;
    m_voxelRenderData.invalidate();
}

void VoxelCluster::removeVoxel(const glm::ivec3& position) {
    Voxel * voxel = m_voxels[position];
    assert(voxel != nullptr);

    m_voxels.erase(position);
    m_voxelRenderData.invalidate();
    delete voxel;
}

VoxelRenderData *VoxelCluster::voxelRenderData() {
    return &m_voxelRenderData;
}

const std::unordered_map<glm::ivec3, Voxel*> & VoxelCluster::voxelMap() const {
    return m_voxels;
}

WorldTransform& VoxelCluster::transform() {
    return m_transform;
}


