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
	VoxelCluster(glm::vec3 center = glm::vec3(0), float scale = 1.0);
    virtual ~VoxelCluster();

    AABB aabb(const WorldTransform & transform);
    Sphere sphere(const WorldTransform & transform);

    Voxel * voxel(cvec3 position);
    virtual void addVoxel(Voxel *voxel);
    virtual void removeVoxel(const cvec3 &position);

    VoxelRenderData *voxelRenderData();

protected:
    void updateTextures();
    
    VoxelRenderData m_voxelRenderData;

    std::unordered_map<cvec3, Voxel*> m_voxels;
    CAABB m_aabb;
};

