#pragma once
#include <map>

#include <glow/Texture.h>
#include <glow/ref_ptr.h>

#include "voxel.h"


// this class contains texture with color and position information about voxel
class VoxelRenderData
{
public:
    VoxelRenderData(std::unordered_map<cvec3, Voxel*> &voxel);
    ~VoxelRenderData();

    void invalidate();

    glow::Texture *positionTexture();
    glow::Texture *colorTexture();
    int voxelCount();

private:
    void updateTextures();
   
    std::unordered_map<cvec3, Voxel*> &m_voxel;
    int m_voxelCount;
    bool m_texturesDirty;
    glow::ref_ptr<glow::Texture> m_positionTexture;
    glow::ref_ptr<glow::Texture> m_colorTexture;
};

