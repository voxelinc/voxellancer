#include "voxelrenderdata.h"

#include <iostream>
#include <vector>

#include <glowutils/MathMacros.h>
#include <glow/DebugMessageOutput.h>

#include "utils/tostring.h"

#include "voxelcluster.h"



VoxelRenderData::VoxelRenderData(std::unordered_map<glm::ivec3, Voxel*> &voxel) :
    m_voxel(voxel),
    m_texturesDirty(true)
{
    m_voxelTexture = new glow::Texture(GL_TEXTURE_2D);
    m_voxelTexture->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    m_voxelTexture->setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


VoxelRenderData::~VoxelRenderData() {
}

void VoxelRenderData::updateTextures() {
    int size = nextPowerOf2(static_cast<int>(glm::ceil(glm::sqrt(m_voxel.size() * 2.0f))));
    size = std::max(4, size);

    std::vector<unsigned char> voxelData(size * size * 3);

    int i = 0;
    for (auto pair : m_voxel) {
        Voxel *voxel = pair.second;
        assert(voxel != nullptr);

        voxelData[i * 6 + 0] = static_cast<unsigned char>(voxel->gridCell().x);
        voxelData[i * 6 + 1] = static_cast<unsigned char>(voxel->gridCell().y);
        voxelData[i * 6 + 2] = static_cast<unsigned char>(voxel->gridCell().z);
        voxelData[i * 6 + 3] = voxel->color() >> 16;
        voxelData[i * 6 + 4] = (voxel->color() & 0xFF00) >> 8;
        voxelData[i * 6 + 5] = voxel->color() & 0xFF;
        i++;
    }
    m_voxelCount = i;
    m_textureSize = size;

    m_voxelTexture->image2D(0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, &voxelData.front());
    CheckGLError();

    m_texturesDirty = false;
}

// returns the number of voxel that will be rendered
int VoxelRenderData::voxelCount() {
    if (m_texturesDirty)
        updateTextures();
    return m_voxelCount;
}

glow::Texture * VoxelRenderData::voxelTexture() {
    if (m_texturesDirty)
        updateTextures();
    return m_voxelTexture;
}

void VoxelRenderData::invalidate() {
    m_texturesDirty = true;
}

int VoxelRenderData::textureSize() {
    return m_textureSize;
}
