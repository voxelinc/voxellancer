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
    m_voxelRenderData(m_voxels),
    m_transform(center, scale)
{
}

VoxelCluster::~VoxelCluster() {
    //TODO: all the cleanup?
}

WorldTransform &VoxelCluster::transform() {
    return m_transform;
}

const WorldTransform &VoxelCluster::transform() const {
    return m_transform;
}

void VoxelCluster::addVoxel(Voxel *voxel) {
    assert(m_voxels.find(voxel->gridCell()) == m_voxels.end());
    m_voxels[voxel->gridCell()] = voxel;
    m_aabb.extend(voxel->gridCell());
    m_voxelRenderData.invalidate();
}

void VoxelCluster::removeVoxel(const cvec3 & position) {
    Voxel * voxel = m_voxels[position];
    m_voxels.erase(position);
    m_voxelRenderData.invalidate();
    delete voxel;
}

AABB VoxelCluster::aabb() {
    return aabb(m_transform);
}
AABB VoxelCluster::aabb(const WorldTransform & transform) {
    return AABB::containing(sphere(transform));
}

Sphere VoxelCluster::sphere() {
    return sphere(m_transform);
}
Sphere VoxelCluster::sphere(const WorldTransform & transform) {
    Sphere sphere;
    sphere.setPosition(transform.applyTo(glm::vec3(0)));
    // m_aabb only contains the center of each voxel so add sqrt(2) to add the distance from center to edge
    sphere.setRadius((glm::length(glm::vec3(m_aabb.rub() - m_aabb.llf())) + glm::root_two<float>()) / 2.f * transform.scale());
    return sphere;
}

VoxelRenderData * VoxelCluster::voxelRenderData() {
    return &m_voxelRenderData;
}

void VoxelCluster::finishInitialization() {

}

Voxel * VoxelCluster::voxel(cvec3 position) {
    return m_voxels[position];
}

