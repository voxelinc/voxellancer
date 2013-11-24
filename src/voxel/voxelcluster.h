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
	VoxelCluster(const VoxelCluster& other);
    virtual ~VoxelCluster();

    virtual void update(float delta_sec);

    AABB aabb();

    WorldTransform &transform();
    const WorldTransform &transform() const;

    VoxeltreeNode &voxeltree();
    const VoxeltreeNode &voxeltree() const;

    WorldtreeGeode *geode();
    const WorldtreeGeode *geode() const;
    void setGeode(WorldtreeGeode *geode);
    void setWorldTree(Worldtree* worldTree);

    void addVoxel(const Voxel & voxel);
    void removeVoxel(const cvec3 &position);

    VoxelRenderData *voxelRenderData();
    const std::unordered_map<cvec3, Voxel, VoxelHash> & voxel() const;

protected:
    void updateTextures();
    void updateGeode();
    

    WorldTransform m_transform;
    VoxeltreeNode m_voxelTree;
    VoxelRenderData m_voxelRenderData;
    WorldtreeGeode *m_geode;
    Worldtree *m_worldTree;
    std::unordered_map<cvec3, Voxel, VoxelHash> m_voxel;
};

