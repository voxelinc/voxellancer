#pragma once

#include <unordered_map>
#include <glow/Texture.h>
#include <glow/ref_ptr.h>

#include "geometry/aabb.h"
#include "worldobject.h"
#include "voxel.h"

class Voxelcluster : public WorldObject
{
public:
    Voxelcluster();
    virtual ~Voxelcluster();

    const AABB &aabb();

    void addVoxel(const Voxel & voxel);
    void removeVoxel(const cvec3 & position);
    int voxelCount();

    glow::Texture * positionTexture();
    glow::Texture * colorTexture();

protected:
    void updateTextures();

    AABB m_aabb;
    std::unordered_map<cvec3, Voxel, VoxelHash> m_voxel;
    bool m_texturesDirty;

    glow::ref_ptr<glow::Texture> m_positionTexture;
    glow::ref_ptr<glow::Texture> m_colorTexture;
};
