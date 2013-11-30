#include <glowutils/MathMacros.h>
#include <glow/DebugMessageOutput.h>

#include "voxelrenderdata.h"
#include "voxelcluster.h"
#include <vector>

VoxelRenderData::VoxelRenderData(std::unordered_map<glm::ivec3, Voxel*> &voxel) :
    m_voxel(voxel),
    m_texturesDirty(true)
{
    m_positionTexture = new glow::Texture(GL_TEXTURE_1D);
    m_positionTexture->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    m_positionTexture->setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    m_colorTexture = new glow::Texture(GL_TEXTURE_1D);
    m_colorTexture->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    m_colorTexture->setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

VoxelRenderData::~VoxelRenderData() {
}

void VoxelRenderData::updateTextures() {
    int size = nextPowerOf2(m_voxel.size());
    std::vector<unsigned char> positionData(size * 3);
    std::vector<unsigned char> colorData(size * 3);

    int i = 0;
    for (auto pair : m_voxel) {
        Voxel *voxel = pair.second;
        positionData[i * 3 + 0] = static_cast<unsigned char>(voxel->gridCell().x);
        positionData[i * 3 + 1] = static_cast<unsigned char>(voxel->gridCell().y);
        positionData[i * 3 + 2] = static_cast<unsigned char>(voxel->gridCell().z);
        colorData[i * 3 + 0] = voxel->color().x;
        colorData[i * 3 + 1] = voxel->color().y;
        colorData[i * 3 + 2] = voxel->color().z;
        i++;
    }
    m_voxelCount = i;

    m_positionTexture->image1D(0, GL_RGB, size, 0, GL_RGB, GL_UNSIGNED_BYTE, &positionData.front());
    m_colorTexture->image1D(0, GL_RGB, size, 0, GL_RGB, GL_UNSIGNED_BYTE, &colorData.front());
    CheckGLError();

    m_texturesDirty = false;
}

// returns the number of voxel that will be rendered
int VoxelRenderData::voxelCount() {
    if (m_texturesDirty)
        updateTextures();
    return m_voxelCount;
}

glow::Texture * VoxelRenderData::positionTexture() {
    if (m_texturesDirty)
        updateTextures();
    return m_positionTexture;
}

glow::Texture * VoxelRenderData::colorTexture() {
    if (m_texturesDirty)
        updateTextures();
    return m_colorTexture;
}

void VoxelRenderData::invalidate() {
    m_texturesDirty = true;
}
