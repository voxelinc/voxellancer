#pragma once

#include <set>
#include <memory>
#include <unordered_map>

#include <glm/glm.hpp>

#include <glow/Texture.h>
#include <glow/ref_ptr.h>

#include "geometry/aabb.h"

#include "worldtransform.h"
#include "voxel.h"
#include "voxelrenderdata.h"
#include "voxelgridcmp.h"


class WorldTreeGeode;
class WorldTree;

class VoxelCluster
{
public:
	VoxelCluster(float scale);
    virtual ~VoxelCluster();

    const WorldTransform& transform();

    const IAABB &gridAABB() const;

    AABB aabb() const;
    AABB aabb(const WorldTransform& transform) const;
    Sphere sphere() const;
    Sphere sphere(const WorldTransform& transform) const;

    Voxel* voxel(const glm::ivec3& position);
    virtual void addVoxel(Voxel* voxel);
    virtual void removeVoxel(Voxel* voxel);

    const std::unordered_map<glm::ivec3, Voxel*>& voxelMap() const;
    int voxelCount() const;

    VoxelRenderData* voxelRenderData();

    void setOrientation(const glm::quat& orientation);
    void setPosition(const glm::vec3& pos);
    void rotate(const glm::quat& param1);
    void move(const glm::vec3& vec3);


protected:
    VoxelRenderData m_voxelRenderData;
    WorldTransform m_transform;
    IAABB m_gridAABB;

    std::unordered_map<glm::ivec3, Voxel*> m_voxels;

    std::set<Voxel*, VoxelGridCmp<XAxis, YAxis, ZAxis>> m_voxelsXSorted;
    std::set<Voxel*, VoxelGridCmp<YAxis, XAxis, ZAxis>> m_voxelsYSorted;
    std::set<Voxel*, VoxelGridCmp<ZAxis, XAxis, YAxis>> m_voxelsZSorted;

    void extendGridAABB(Voxel* voxel);
    void shrinkGridAABB(Voxel* voxel);
};

