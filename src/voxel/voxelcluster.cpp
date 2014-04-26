#include "voxelcluster.h"

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
    m_transform(glm::vec3(0), scale),
    m_emissiveness(0.0f)
{
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

float VoxelCluster::emissiveness() const {
    return m_emissiveness;
}

void VoxelCluster::setEmissiveness(float emissiveness) {
    m_emissiveness = emissiveness;
}

Voxel* VoxelCluster::voxel(const glm::ivec3& position) {
    auto iter = m_voxels.find(position);
    return iter == m_voxels.end() ? nullptr : iter->second;
}

const Voxel* VoxelCluster::voxel(const glm::ivec3& position) const {
    auto iter = m_voxels.find(position);
    return iter == m_voxels.end() ? nullptr : iter->second;
}

void VoxelCluster::addVoxel(Voxel* voxel) {
    assert(m_voxels[voxel->gridCell()] == nullptr);

    m_voxels[voxel->gridCell()] = voxel;
    m_bounds->addVoxel(voxel);
    m_voxelRenderData->invalidate();
}

void VoxelCluster::removeVoxel(Voxel* voxel) {
    assert(voxel != nullptr);

    m_bounds->removeVoxel(voxel); // Needs to be done before removal from m_voxels
    m_voxels.erase(voxel->gridCell());
    m_voxelRenderData->invalidate();

    delete voxel;
}

VoxelRenderData* VoxelCluster::voxelRenderData(){
    return m_voxelRenderData.get();
}

const std::unordered_map<glm::ivec3, Voxel*>& VoxelCluster::voxelMap() const {
    return m_voxels;
}

int VoxelCluster::voxelCount() const {
    return m_voxels.size();
}


