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
    for (auto& element : m_voxels){
        delete element.second;
    }
}

Voxel* VoxelCluster::voxel(const glm::ivec3& position) {
    std::unordered_map<glm::ivec3, Voxel*>::iterator i = m_voxels.find(position);
    return i == m_voxels.end() ? nullptr : i->second;
}

void VoxelCluster::addVoxel(Voxel* voxel) {
    assert(m_voxels[voxel->gridCell()] == nullptr);

    m_voxels[voxel->gridCell()] = voxel;
    m_voxelRenderData.invalidate();
}

void VoxelCluster::removeVoxel(Voxel* voxel) {
    assert(voxel != nullptr);

    m_voxels.erase(voxel->gridCell());
    m_voxelRenderData.invalidate();
    delete voxel;
}

VoxelRenderData *VoxelCluster::voxelRenderData() {
    return &m_voxelRenderData;
}

const std::unordered_map<glm::ivec3, Voxel*>& VoxelCluster::voxelMap() const {
    return m_voxels;
}

int VoxelCluster::voxelCount() const {
    return m_voxels.size();
}

const WorldTransform& VoxelCluster::transform() {
    return m_transform;
}

void VoxelCluster::rotate(const glm::quat& rotation) {
    m_transform.rotate(rotation);
}

void VoxelCluster::move(const glm::vec3& vec3) {
    m_transform.move(vec3);
}

void VoxelCluster::setOrientation(const glm::quat& orientation) {
    m_transform.setOrientation(orientation);
}

void VoxelCluster::setPosition(const glm::vec3& pos) {
    m_transform.setPosition(pos);
}
