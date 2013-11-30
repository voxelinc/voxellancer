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


VoxelCluster::VoxelCluster(glm::vec3 center, float scale):
    m_voxels(),
    m_voxelRenderData(m_voxels)
{
}

VoxelCluster::~VoxelCluster() {
    // free all clusters
    for (auto& element : m_voxels){
        delete element.second;
    }
}

Voxel* VoxelCluster::voxel(const glm::ivec3& position) {
    return m_voxels[position];
}

void VoxelCluster::addVoxel(Voxel *voxel) {
    assert(m_voxels.find(voxel->gridCell()) == m_voxels.end());

    m_voxels[voxel->gridCell()] = voxel;
    m_aabb.extend(voxel->gridCell());
    m_voxelRenderData.invalidate();
}

void VoxelCluster::removeVoxel(const const glm::ivec3& position) {
    Voxel * voxel = m_voxels[position];
    assert(voxel != nullptr);
    m_voxels.erase(position);
    m_voxelRenderData.invalidate();
    delete voxel;
}

AABB VoxelCluster::aabb(const WorldTransform& transform) {
    return AABB::containing(sphere(transform));
}

Sphere VoxelCluster::sphere(const WorldTransform& transform) {
    Sphere sphere;
    sphere.setPosition(transform.applyTo(glm::vec3(0)));
    // m_aabb only contains the center of each voxel so add sqrt(2) to add the distance from center to edge
    sphere.setRadius((glm::length(glm::vec3(m_aabb.rub() - m_aabb.llf())) + glm::root_two<float>()) / 2.f * transform.scale());
    return sphere;
}

VoxelRenderData * VoxelCluster::voxelRenderData() {
    return &m_voxelRenderData;
}
