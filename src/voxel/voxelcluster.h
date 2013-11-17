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


class WorldtreeGeode;
class Worldtree;

class VoxelCluster
{
public:
    VoxelCluster(glm::vec3 center = glm::vec3(0), float scale = 1.0);
    virtual ~VoxelCluster();

    AABB aabb();

    WorldTransform &transform();
    const WorldTransform &transform() const;

    void applyTransform(bool checkCollision = true);


    VoxeltreeNode &voxeltree();
    const VoxeltreeNode &voxeltree() const;

    WorldtreeGeode *geode();
    const WorldtreeGeode *geode() const;
    void setGeode(WorldtreeGeode *geode);
    void setWorldTree(Worldtree* worldTree);

    void addVoxel(const Voxel &voxel);
    void removeVoxel(const cvec3 &position);

    VoxelRenderData *voxelRenderData();
    const std::unordered_map<cvec3, Voxel, VoxelHash> & voxel() const;

protected:
    void updateTextures();
    void updateGeode();
    void doSteppedTransform();
    bool isPossibleCollision();

    WorldTransform m_transform;
    WorldTransform m_old_transform;
    VoxeltreeNode m_voxeltree;
    VoxelRenderData m_voxelrenderdata;
    WorldtreeGeode *m_geode;
    Worldtree *m_worldTree;
    std::unordered_map<cvec3, Voxel, VoxelHash> m_voxel;
};

