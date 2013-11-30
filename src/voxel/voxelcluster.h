#pragma once

#include <unordered_map>

#include <glm/glm.hpp>

#include <glow/Texture.h>
#include <glow/ref_ptr.h>

#include "geometry/aabb.h"

#include "voxeltreenode.h"
#include "worldtransform.h"
#include "voxel.h"
#include "voxelrenderdata.h"
#include <memory>


class WorldTreeGeode;
class WorldTree;

class VoxelCluster
{
public:
	VoxelCluster();
    virtual ~VoxelCluster();

    AABB aabb(const WorldTransform& transform);
    Sphere sphere(const WorldTransform& transform);

    Voxel* voxel(const glm::ivec3& position);
    virtual void addVoxel(Voxel* voxel);
    virtual void removeVoxel(const glm::ivec3& position);

    VoxelRenderData *voxelRenderData();


protected:
    VoxelRenderData m_voxelRenderData;

    std::unordered_map<glm::ivec3, Voxel*> m_voxels;
    IAABB m_aabb;
};

