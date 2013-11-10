#pragma once

#include <unordered_map>

#include <glm/glm.hpp>

#include <glow/Texture.h>
#include <glow/ref_ptr.h>

#include "geometry/aabb.h"

#include "voxeltreenode.h"
#include "worldtransform.h"
#include "voxel.h"


class WorldtreeGeode;

class VoxelCluster : public WorldTransform
{
public:
    VoxelCluster();
    virtual ~VoxelCluster();

    const AABB &aabb();

    const glm::vec3 &center() const;
    void setCenter(const glm::vec3 &center);

//    const WorldTransform &worldTransform() const;
//    void setWorldTransform(const WorldTransform &transform);

    VoxeltreeNode &voxeltree();
    const VoxeltreeNode &voxeltree() const;

    WorldtreeGeode *geode();
    const WorldtreeGeode *geode() const;
    void setGeode(WorldtreeGeode *geode);

    void addVoxel(const Voxel & voxel);
    void removeVoxel(const cvec3 & position);
    int voxelCount();

    glow::Texture * positionTexture();
    glow::Texture * colorTexture();

protected:
    void updateTextures();


    glm::vec3 m_center;
//    WorldTransform m_worldTransform;
    VoxeltreeNode m_voxeltree;
    WorldtreeGeode *m_geode;
    AABB m_aabb;
    std::unordered_map<cvec3, Voxel, VoxelHash> m_voxel;
    bool m_texturesDirty;

    glow::ref_ptr<glow::Texture> m_positionTexture;
    glow::ref_ptr<glow::Texture> m_colorTexture;
};

