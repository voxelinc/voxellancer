#pragma once

#include <set>
#include <memory>
#include <unordered_map>

#include <glm/glm.hpp>

#include "geometry/aabb.h"
#include "geometry/transform.h"

#include "utils/vec3hash.h"

#include "voxelclusterbounds.h"
#include "voxelgridcmp.h"
#include "voxelrenderdata.h"


class Voxel;
class VoxelRenderData;

class VoxelCluster {
public:
    VoxelCluster(float scale);
    virtual ~VoxelCluster();

    VoxelClusterBounds& bounds();

    Transform& transform();
    void setTransform(const Transform& transform);

    Voxel* voxel(const glm::ivec3& position);

    virtual void addVoxel(Voxel* voxel);
    virtual void removeVoxel(Voxel* voxel);

    const std::unordered_map<glm::ivec3, Voxel*>& voxelMap() const;
    int voxelCount() const;

    VoxelRenderData* voxelRenderData();

    virtual float emissiveness() const;


protected:
    std::unordered_map<glm::ivec3, Voxel*> m_voxels;
    VoxelClusterBounds m_bounds;
    VoxelRenderData m_voxelRenderData;
    Transform m_transform;
};

