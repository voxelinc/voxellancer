#include "voxelcluster.h"

#include "glowutils/MathMacros.h"
#include "glow/DebugMessageOutput.h"

Voxelcluster::Voxelcluster():
    WorldObject(),
    m_texturesDirty(true),
    m_voxel(),
    m_aabb()
{
    m_positionTexture = new glow::Texture(GL_TEXTURE_1D);
    m_positionTexture->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    m_positionTexture->setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    m_colorTexture = new glow::Texture(GL_TEXTURE_1D);
    m_colorTexture->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    m_colorTexture->setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}

Voxelcluster::~Voxelcluster() {

}

const AABB &Voxelcluster::aabb() {
    return m_aabb;
}

void Voxelcluster::addVoxel(const Voxel & voxel)
{
    // TODO aabb extent(vec3)
    m_voxel[voxel.position()] = voxel;

    m_texturesDirty = true;
}

void Voxelcluster::removeVoxel(const cvec3 & position)
{
    m_voxel.erase(position);
    m_texturesDirty = true;
}

glow::Texture * Voxelcluster::positionTexture()
{
    if (m_texturesDirty)
        updateTextures();
    return m_positionTexture;
}

glow::Texture * Voxelcluster::colorTexture()
{
    if (m_texturesDirty)
        updateTextures();
    return m_colorTexture;
}

void Voxelcluster::updateTextures()
{
    int size = nextPowerOf2(m_voxel.size());
    signed char * positionData = new signed char[size*3];
    unsigned char * colorData = new unsigned char[size*3];

    int i = 0;
    for (auto pair: m_voxel)
    {
        Voxel voxel = pair.second;
        positionData[i * 3 + 0] = voxel.position().x+128;
        positionData[i * 3 + 1] = voxel.position().y+128;
        positionData[i * 3 + 2] = voxel.position().z+128;
        colorData[i * 3 + 0] = voxel.color().x;
        colorData[i * 3 + 1] = voxel.color().y;
        colorData[i * 3 + 2] = voxel.color().z;
        i++;
    }

    m_positionTexture->image1D(0, GL_RGB, size, 0, GL_RGB, GL_UNSIGNED_BYTE, positionData);
    m_colorTexture->image1D(0, GL_RGB, size, 0, GL_RGB, GL_UNSIGNED_BYTE, colorData);
    CheckGLError();

    delete[] colorData;
    delete[] positionData;

    m_texturesDirty = false;
}

int Voxelcluster::voxelCount()
{
    return m_voxel.size();
}

