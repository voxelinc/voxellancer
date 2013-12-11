#pragma once

#include <unordered_map>

#include <glm/glm.hpp>

#include <glow/Texture.h>
#include <glow/ref_ptr.h>

#include "geometry/aabb.h"

#include "worldtransform.h"
#include "voxel.h"
#include "voxelrenderdata.h"
#include <memory>


class WorldTreeGeode;
class WorldTree;

class VoxelCluster
{
public:
	VoxelCluster(float scale);
    virtual ~VoxelCluster();

    const WorldTransform& transform();

    Voxel* voxel(const glm::ivec3& position);
    virtual void addVoxel(Voxel* voxel);
    virtual void removeVoxel(const glm::ivec3& position);
    const std::unordered_map<glm::ivec3, Voxel*>& voxelMap() const;
    int voxelCount() const;

    VoxelRenderData *voxelRenderData();

    void setOrientation(const glm::quat& orientation);
    void setPosition(const glm::vec3& pos);
    void rotate(const glm::quat& param1);
    void move(const glm::vec3& vec3);

protected:
    VoxelRenderData m_voxelRenderData;
    WorldTransform m_transform;

    std::unordered_map<glm::ivec3, Voxel*> m_voxels;
};

