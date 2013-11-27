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


class WorldtreeGeode;
class Worldtree;

class VoxelCluster
{
public:
	VoxelCluster(glm::vec3 center = glm::vec3(0), float scale = 1.0);
    virtual ~VoxelCluster();

    AABB aabb();
    Sphere sphere();

    WorldTransform &transform();
    const WorldTransform &transform() const;

    virtual void addVoxel(Voxel *voxel);
    virtual void removeVoxel(const cvec3 &position);

    VoxelRenderData *voxelRenderData();
    const std::unordered_map<cvec3, Voxel*, VoxelHash> & voxel() const;

    virtual void finishInitialization();

protected:
    void updateTextures();
    
    AABB aabb(const WorldTransform & transform);
    Sphere sphere(const WorldTransform & transform);

    WorldTransform m_transform;
    VoxelRenderData m_voxelRenderData;

    std::unordered_map<cvec3, Voxel*, VoxelHash> m_voxel;
    CAABB m_aabb;
};

