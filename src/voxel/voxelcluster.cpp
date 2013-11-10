#include "voxelcluster.h"

#include "glowutils/MathMacros.h"
#include "glow/DebugMessageOutput.h"

#include "worldtree/worldtreegeode.h"


VoxelCluster::VoxelCluster():
    WorldTransform(),
    m_texturesDirty(true),
    m_voxel(),
    m_aabb(),
    m_voxeltree(nullptr, *this, IAABB(glm::ivec3(0, 0, 0), glm::ivec3(1, 1, 1)))
{
    m_positionTexture = new glow::Texture(GL_TEXTURE_1D);
    m_positionTexture->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    m_positionTexture->setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    m_colorTexture = new glow::Texture(GL_TEXTURE_1D);
    m_colorTexture->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    m_colorTexture->setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

VoxelCluster::~VoxelCluster() {

}

const AABB &VoxelCluster::aabb() {
    return m_aabb;
}

const glm::vec3 &VoxelCluster::center() const {
    return m_center;
}

void VoxelCluster::setCenter(const glm::vec3 &center) {
    m_center = center;
}

//const WorldTransform &VoxelCluster::worldTransform() const {
//    return m_worldTransform;
//}
//
//void VoxelCluster::setWorldTransform(const WorldTransform &transform) {
//    m_worldTransform = transform;
//}

VoxeltreeNode &VoxelCluster::voxeltree() {
    return m_voxeltree;
}

const VoxeltreeNode &VoxelCluster::voxeltree() const {
    return m_voxeltree;
}

WorldtreeGeode *VoxelCluster::geode() {
    return m_geode;
}

const WorldtreeGeode *VoxelCluster::geode() const {
    return m_geode;
}

void VoxelCluster::setGeode(WorldtreeGeode *geode) {
    m_geode = geode;
}

void VoxelCluster::addVoxel(const Voxel & voxel) {
    // TODO aabb extent(vec3)
    m_voxel[voxel.position()] = voxel;

    m_texturesDirty = true;
}

void VoxelCluster::removeVoxel(const cvec3 & position) {
    m_voxel.erase(position);
    m_texturesDirty = true;
}

glow::Texture * VoxelCluster::positionTexture() {
    if (m_texturesDirty)
        updateTextures();
    return m_positionTexture;
}

glow::Texture * VoxelCluster::colorTexture() {
    if (m_texturesDirty)
        updateTextures();
    return m_colorTexture;
}

void VoxelCluster::updateTextures() {
    int size = nextPowerOf2(m_voxel.size());
    unsigned char * positionData = new unsigned char[size*3];
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

int VoxelCluster::voxelCount() {
    return m_voxel.size();
}


