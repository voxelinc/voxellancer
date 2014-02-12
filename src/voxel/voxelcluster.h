#pragma once

#include <set>
#include <memory>
#include <unordered_map>

#include <glm/glm.hpp>

#include "geometry/aabb.h"
#include "geometry/transform.h"

#include "utils/vec3hash.h"
#include "voxelclusterbounds.h"


class Voxel;
class VoxelRenderData;

class VoxelCluster {
public:
    VoxelCluster(float scale);
    virtual ~VoxelCluster();

    VoxelClusterBounds& bounds();

    Transform& transform();
    const Transform& transform() const;
    void setTransform(const Transform& transform);

    Voxel* voxel(const glm::ivec3& position);

    virtual void addVoxel(Voxel* voxel);
    virtual void removeVoxel(Voxel* voxel);

    const std::unordered_map<glm::ivec3, Voxel*>& voxelMap() const;
    int voxelCount() const;

    VoxelRenderData* voxelRenderData();

    const glm::vec3& position();
    const glm::quat& orientation();
    void setOrientation(const glm::quat& orientation);
    void setPosition(const glm::vec3& pos);

    void rotate(const glm::quat& param1);
    void move(const glm::vec3& vec3);

    virtual float emissiveness();


protected:
    std::unordered_map<glm::ivec3, Voxel*> m_voxels;
    std::unique_ptr<VoxelRenderData> m_voxelRenderData;

    Transform m_transform;
    VoxelClusterBounds m_bounds;
};

