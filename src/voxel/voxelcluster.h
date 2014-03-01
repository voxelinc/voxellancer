#pragma once

#include <set>
#include <memory>
#include <unordered_map>

#include <glm/glm.hpp>

#include "geometry/transform.h"

#include "utils/vec3hash.h"


class Voxel;
class IVoxelRenderData;
class VoxelClusterBounds;

class VoxelCluster {
public:
    VoxelCluster(float scale);
    virtual ~VoxelCluster();

    VoxelClusterBounds& bounds();

    Transform& transform();
    const Transform& transform() const;
    void setTransform(const Transform& transform);

    const glm::vec3& position() const;
    const glm::quat& orientation() const;

    Voxel* voxel(const glm::ivec3& position);

    virtual void addVoxel(Voxel* voxel);
    virtual void removeVoxel(Voxel* voxel);

    const std::unordered_map<glm::ivec3, Voxel*>& voxelMap() const;
    int voxelCount() const;

    IVoxelRenderData& voxelRenderData();

    virtual float emissiveness() const;

    bool isInstanced();

protected:
    std::unordered_map<glm::ivec3, Voxel*> m_voxels;
    std::unique_ptr<IVoxelRenderData> m_voxelRenderData;
    std::unique_ptr<VoxelClusterBounds> m_bounds;

    Transform m_transform;

    VoxelCluster(VoxelCluster* prototype);
};

