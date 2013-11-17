#pragma once

#include <glow/Texture.h>
#include <glow/ref_ptr.h>

class VoxelCluster;

// this class contains texture with color and position information about voxel
class VoxelRenderData
{
public:
    VoxelRenderData(VoxelCluster * cluster);
    ~VoxelRenderData();

    void invalidate();

    glow::Texture *positionTexture();
    glow::Texture *colorTexture();
    int voxelCount();

private:
    void updateTextures();
   
    VoxelCluster * m_cluster;
    int m_voxelCount;
    bool m_texturesDirty;
    glow::ref_ptr<glow::Texture> m_positionTexture;
    glow::ref_ptr<glow::Texture> m_colorTexture;
};

