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
    m_transform(glm::vec3(0), scale),
    m_minimalGridSphereValid(false),
    m_minimalGridAABBValid(false),
    m_aabbValid(false)
{
}

VoxelCluster::~VoxelCluster() {
    for (auto& element : m_voxels){
        delete element.second;
    }
}

WorldTransform& VoxelCluster::transform() {
    return m_transform;
}

const WorldTransform& VoxelCluster::transform() const {
    return m_transform;
}

const IAABB& VoxelCluster::minimalGridAABB() {
    if(!m_minimalGridAABBValid) {
        calculateMinimalGridAABB();
    }
    return m_minimalGridAABB;
}

const Sphere& VoxelCluster::minimalGridSphere() {
    if(!m_minimalGridSphereValid) {
        calculateMinimalGridSphere();
    }
    return m_minimalGridSphere;
}

const IAABB& VoxelCluster::aabb() {
    if(!m_aabbValid || m_transform != m_cachedAABBTransform) {
        m_aabb = calculateAABB(m_transform);
        m_cachedAABBTransform = m_transform;
        m_aabbValid = true;
    }
    return m_aabb;
}

IAABB VoxelCluster::aabb(const WorldTransform& transform) {
    return calculateAABB(transform);
}

void VoxelCluster::setTransform(const WorldTransform& transform) {
    m_transform = transform;
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

VoxelRenderData* VoxelCluster::voxelRenderData() {
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
    m_voxelsXSorted.insert(voxel);
    m_voxelsYSorted.insert(voxel);
    m_voxelsZSorted.insert(voxel);

    m_minimalGridSphereValid = false;
    m_minimalGridAABBValid = false;
    m_aabbValid = false;
}

void VoxelCluster::shrinkGridAABB(Voxel* voxel) {
    m_voxelsXSorted.erase(voxel);
    m_voxelsYSorted.erase(voxel);
    m_voxelsZSorted.erase(voxel);

    m_minimalGridSphereValid = false;
    m_minimalGridAABBValid = false;
    m_aabbValid = false;
}

void VoxelCluster::calculateMinimalGridAABB() {
    if(voxelCount() != 0) {
        m_minimalGridAABB = IAABB(
            glm::ivec3((*m_voxelsXSorted.begin())->gridCell().x, (*m_voxelsYSorted.begin())->gridCell().y, (*m_voxelsZSorted.begin())->gridCell().z),
            glm::ivec3((*m_voxelsXSorted.rbegin())->gridCell().x, (*m_voxelsYSorted.rbegin())->gridCell().y, (*m_voxelsZSorted.rbegin())->gridCell().z)
        );
    }
    else {
        m_minimalGridAABB = IAABB(glm::ivec3(0, 0, 0), glm::ivec3(0, 0, 0));
    }
    m_minimalGridAABBValid = true;
}

void VoxelCluster::calculateMinimalGridSphere() {
    m_minimalGridSphere.setPosition(glm::vec3(minimalGridAABB().rub() + minimalGridAABB().llf()) / 2.0f);
    // m_gridAABB only contains the center of each voxel so add sqrt(2) to add the distance from center to edge
    m_minimalGridSphere.setRadius((glm::length(glm::vec3(minimalGridAABB().rub() - minimalGridAABB().llf())) + glm::root_two<float>()) / 2.f);
    m_minimalGridSphereValid = true;
}

IAABB VoxelCluster::calculateAABB(const WorldTransform& transform) {
    glm::vec3 middle = transform.applyTo(minimalGridSphere().position());
    float radius = minimalGridSphere().radius() * transform.scale();

    glm::ivec3 llf(static_cast<glm::ivec3>(middle - glm::vec3(radius, radius, radius)));
    glm::ivec3 rub(static_cast<glm::ivec3>(middle + glm::vec3(radius + 1, radius + 1, radius + 1)));

    return IAABB(llf, rub);
}

float VoxelCluster::emissiveness() {
    return 0.0f;
}

