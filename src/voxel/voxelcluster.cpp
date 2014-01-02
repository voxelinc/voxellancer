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

const WorldTransform& VoxelCluster::transform() {
    return m_transform;
}

const IAABB &VoxelCluster::gridAABB() const {
    return m_gridAABB;
}

IAABB VoxelCluster::aabb() const {
    return aabb(m_transform);
}

IAABB VoxelCluster::aabb(const WorldTransform& transform) const {
    Sphere sphere = this->sphere(transform);

    return TAABB<int>(
        glm::ivec3(sphere.position() - glm::vec3(sphere.radius(), sphere.radius(), sphere.radius())),
        glm::ivec3(sphere.position() + glm::vec3(sphere.radius(), sphere.radius(), sphere.radius())) + glm::ivec3(1, 1, 1)
    );
}

Sphere VoxelCluster::sphere() const {
    return sphere(m_transform);
}

Sphere VoxelCluster::sphere(const WorldTransform& transform) const {
    Sphere sphere;
    sphere.setPosition(transform.applyTo(glm::vec3(m_gridAABB.rub() + m_gridAABB.llf()) / 2.0f));
    // m_gridAABB only contains the center of each voxel so add sqrt(2) to add the distance from center to edge
    sphere.setRadius((glm::length(glm::vec3(m_gridAABB.rub() - m_gridAABB.llf())) + glm::root_two<float>()) / 2.f * transform.scale());
    return sphere;
}

Voxel* VoxelCluster::voxel(const glm::ivec3& position) {
    std::unordered_map<glm::ivec3, Voxel*>::iterator i = m_voxels.find(position);
    return i == m_voxels.end() ? nullptr : i->second;
}

void VoxelCluster::addVoxel(Voxel* voxel) {
    assert(m_voxels[voxel->gridCell()] == nullptr);

    m_voxels[voxel->gridCell()] = voxel;
    m_voxelRenderData.invalidate();

    extendGridAABB(voxel);
}

void VoxelCluster::removeVoxel(Voxel* voxel) {
    assert(voxel != nullptr);

    shrinkGridAABB(voxel);

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

void VoxelCluster::extendGridAABB(Voxel* voxel) {
    glm::ivec3 cell = voxel->gridCell();
    if(voxelCount() == 0) {
        m_gridAABB = IAABB(cell, cell);
    }
    else {
        m_gridAABB.extend(cell);
    }

    m_voxelsXSorted.insert(voxel);
    m_voxelsYSorted.insert(voxel);
    m_voxelsZSorted.insert(voxel);
}

void VoxelCluster::shrinkGridAABB(Voxel* voxel) {
    m_voxelsXSorted.erase(voxel);
    m_voxelsYSorted.erase(voxel);
    m_voxelsZSorted.erase(voxel);

    if(!m_voxelsXSorted.empty()) {
        assert(!m_voxelsYSorted.empty() && !m_voxelsZSorted.empty());
        m_gridAABB.setLlf(glm::ivec3((*m_voxelsXSorted.begin())->gridCell().x, (*m_voxelsYSorted.begin())->gridCell().y, (*m_voxelsZSorted.begin())->gridCell().z));
        m_gridAABB.setRub(glm::ivec3((*m_voxelsXSorted.rbegin())->gridCell().x, (*m_voxelsYSorted.rbegin())->gridCell().y, (*m_voxelsZSorted.rbegin())->gridCell().z));
    }
    else {
        m_gridAABB = IAABB(glm::ivec3(0, 0, 0), glm::ivec3(0, 0, 0));
    }
}
