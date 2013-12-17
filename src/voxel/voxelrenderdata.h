#pragma once

#include <unordered_map>

#include <glow/Texture.h>
#include <glow/ref_ptr.h>

#include "voxel.h"


// this class contains texture with color and position information about voxel
class VoxelRenderData
{
public:
    VoxelRenderData(std::unordered_map<glm::ivec3, Voxel*> &voxel);
    ~VoxelRenderData();

    void invalidate();

    glow::Texture *voxelTexture();
    int voxelCount();
    int textureSize();

private:
    void updateTextures();

    std::unordered_map<glm::ivec3, Voxel*> &m_voxel;
    int m_voxelCount;
    int m_textureSize;
    bool m_texturesDirty;
    glow::ref_ptr<glow::Texture> m_voxelTexture;
};

