#include "voxelcluster.h"

#include <iostream>

#include "glowutils/MathMacros.h"
#include "glow/DebugMessageOutput.h"

#include "utils/tostring.h"

#include "worldtree/worldtreegeode.h"


VoxelCluster::VoxelCluster(float edgeLength):
    m_voxelEdgeLength(edgeLength),
    m_texturesDirty(true),
    m_voxel(),
    m_voxeltree(nullptr, *this, Grid3dAABB(glm::ivec3(0, 0, 0), glm::ivec3(0, 0, 0))),
    m_geode(nullptr)
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

AABB VoxelCluster::aabb() {
    return AABB::containing(m_voxeltree.boundingSphere());
}

const glm::vec3 &VoxelCluster::centerInGrid() const {
    return m_centerInGrid;
}

void VoxelCluster::setCenterInGrid(const glm::vec3 &centerInGrid) {
    m_centerInGrid = centerInGrid;

    if(m_geode != nullptr) {
        m_geode->setAABB(aabb());
    }
}

const WorldTransform &VoxelCluster::worldTransform() const {
    return m_worldTransform;
}

void VoxelCluster::setWorldTransform(const WorldTransform &transform) {
    m_worldTransform = transform;

    if(m_geode != nullptr) {
        m_geode->setAABB(aabb());
    }
}

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

    if(m_geode != nullptr) {
        m_geode->setAABB(aabb());
    }
}

float VoxelCluster::voxelEdgeLength() const {
    return m_voxelEdgeLength;
}

void VoxelCluster::setVoxelEdgeLength(float voxelEdgeLength) {
    m_voxelEdgeLength = voxelEdgeLength;

    if(m_geode != nullptr) {
        m_geode->setAABB(aabb());
    }
}

void VoxelCluster::addVoxel(const Voxel & voxel) {
    // TODO aabb extent(vec3)
    m_voxel[voxel.gridCell()] = voxel;

    // Memoryleak as of now, voxeltree shouldn't manage the voxel
    m_voxeltree.insert(new Voxel(voxel));

    m_texturesDirty = true;

    if(m_geode != nullptr) {
        m_geode->setAABB(aabb());
    }
}

void VoxelCluster::removeVoxel(const cvec3 & position) {
    m_voxel.erase(position);
    m_voxeltree.remove(position);
    m_texturesDirty = true;
}


void VoxelCluster::updateTextures() {
    int size = nextPowerOf2(m_voxel.size());
    unsigned char * positionData = new unsigned char[size*3];
    unsigned char * colorData = new unsigned char[size*3];

    int i = 0;
    for (auto pair: m_voxel)
    {
        Voxel voxel = pair.second;
        positionData[i * 3 + 0] = voxel.gridCell().x+128;
        positionData[i * 3 + 1] = voxel.gridCell().y+128;
        positionData[i * 3 + 2] = voxel.gridCell().z+128;
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

void VoxelCluster::transform(const WorldTransform &t) {
    m_worldTransform.transform(t);

    if(m_geode != nullptr) {
        m_geode->setAABB(aabb());
    }
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

