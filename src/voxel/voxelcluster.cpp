#include "voxelcluster.h"

#include <iostream>
#include <list>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <glow/ChangeListener.h>
#include <glow/logging.h>

#include "resource/clustercache.h"

#include "utils/tostring.h"

#include "voxelrenderdata.h"
#include "voxel.h"
#include "voxelclusterbounds.h"


VoxelCluster::VoxelCluster(float scale):
    m_voxels(),
    m_bounds(new VoxelClusterBounds(this)),
    m_voxelRenderData(new VoxelRenderData(m_voxels)),
    m_transform(glm::vec3(0), scale)
{
}

VoxelCluster::VoxelCluster(VoxelCluster* prototype):
    m_voxels(),
    m_bounds(new VoxelClusterBounds(prototype->bounds())),
    m_voxelRenderData(new InstancedVoxelRenderData(prototype->voxelRenderData())),
    m_transform(prototype->transform())
{
    assert(!prototype->voxelRenderData().isInstanced());
}

VoxelCluster::~VoxelCluster() {
    for (auto& element : m_voxels) {
        delete element.second;
    }
}

VoxelClusterBounds& VoxelCluster::bounds() {
    return *m_bounds;
}

Transform& VoxelCluster::transform() {
    return m_transform;
}

const Transform& VoxelCluster::transform() const {
    return m_transform;
}

void VoxelCluster::setTransform(const Transform& transform) {
    m_transform = transform;
}

const glm::vec3& VoxelCluster::position() const {
    return m_transform.position();
}

const glm::quat& VoxelCluster::orientation() const {
    return m_transform.orientation();
}

Voxel* VoxelCluster::voxel(const glm::ivec3& position) {
    assert(!m_voxelRenderData->isInstanced());
    std::unordered_map<glm::ivec3, Voxel*>::iterator i = m_voxels.find(position);
    return i == m_voxels.end() ? nullptr : i->second;
}

void VoxelCluster::addVoxel(Voxel* voxel) {
    assert(!m_voxelRenderData->isInstanced());
    assert(m_voxels[voxel->gridCell()] == nullptr);

    m_voxels[voxel->gridCell()] = voxel;
    m_bounds->addVoxel(voxel);
    m_voxelRenderData->invalidate();
}

void VoxelCluster::removeVoxel(Voxel* voxel) {
    assert(!m_voxelRenderData->isInstanced());
    assert(voxel != nullptr);

    m_bounds->removeVoxel(voxel); // Needs to be done before removal from m_voxels
    m_voxels.erase(voxel->gridCell());
    m_voxelRenderData->invalidate();

    delete voxel;
}

IVoxelRenderData& VoxelCluster::voxelRenderData() {
    return *m_voxelRenderData;
}

const std::unordered_map<glm::ivec3, Voxel*>& VoxelCluster::voxelMap() const {
    assert(!m_voxelRenderData->isInstanced());
    return m_voxels;
}

int VoxelCluster::voxelCount() const {
    assert(!m_voxelRenderData->isInstanced());
    return m_voxels.size();
}

float VoxelCluster::emissiveness() const {
    return 0.0f;
}

