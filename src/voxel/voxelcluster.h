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

class VoxelCluster //: public WorldTransform
{
public:
    VoxelCluster(float voxelEdgeLength = 1.0f);
	VoxelCluster(const VoxelCluster& other);
    virtual ~VoxelCluster();

    AABB aabb();

    const glm::vec3 &centerInGrid() const;
    void setCenterInGrid(const glm::vec3 &centerInGrid);

    const WorldTransform &worldTransform() const;
    void setWorldTransform(const WorldTransform &transform);

    VoxeltreeNode &voxeltree();
    const VoxeltreeNode &voxeltree() const;

    WorldtreeGeode *geode();
    const WorldtreeGeode *geode() const;
    void setGeode(WorldtreeGeode *geode);

    float voxelEdgeLength() const;
    void setVoxelEdgeLength(float voxelEdgeLength);

    void addVoxel(const Voxel &voxel);
    void removeVoxel(const cvec3 &position);

    int voxelCount();

    void move(glm::vec3 dist);

	void rotateX(float rot);
	void rotateY(float rot);
	void rotateZ(float rot);

	void transform(const WorldTransform &t);

    glow::Texture *positionTexture();
    glow::Texture *colorTexture();


protected:
    void updateAABB();
    void updateTextures();

    float m_voxelEdgeLength;
    glm::vec3 m_centerInGrid;
    WorldTransform m_worldTransform;
    VoxeltreeNode m_voxeltree;
    WorldtreeGeode *m_geode;
    std::unordered_map<cvec3, Voxel, VoxelHash> m_voxel;
    bool m_texturesDirty;

    glow::ref_ptr<glow::Texture> m_positionTexture;
    glow::ref_ptr<glow::Texture> m_colorTexture;
};

