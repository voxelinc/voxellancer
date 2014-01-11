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


class VoxelCluster
{
public:
	VoxelCluster(float scale);
    virtual ~VoxelCluster();

    WorldTransform& transform();
    const WorldTransform& transform() const;
    void setTransform(const WorldTransform& transform);


    const IAABB& minimalGridAABB();

    const Sphere& minimalGridSphere();

    const IAABB& aabb();
    IAABB aabb(const WorldTransform& transform);

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

    std::unordered_map<glm::ivec3, Voxel*> m_voxels;

    std::set<Voxel*, VoxelGridCmp<XAxis, YAxis, ZAxis>> m_voxelsXSorted;
    std::set<Voxel*, VoxelGridCmp<YAxis, XAxis, ZAxis>> m_voxelsYSorted;
    std::set<Voxel*, VoxelGridCmp<ZAxis, XAxis, YAxis>> m_voxelsZSorted;


    void extendGridAABB(Voxel* voxel);
    void shrinkGridAABB(Voxel* voxel);

    void calculateMinimalGridAABB();
    void calculateMinimalGridSphere();
    IAABB calculateAABB(const WorldTransform& transform);


private:
    IAABB m_minimalGridAABB;
    bool m_minimalGridAABBValid;

    Sphere m_minimalGridSphere;
    bool m_minimalGridSphereValid;

    IAABB m_aabb;
    WorldTransform m_cachedAABBTransform;
    bool m_aabbValid;
};

