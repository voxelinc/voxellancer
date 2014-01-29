#pragma once

#include <set>
#include <memory>
#include <unordered_map>

#include <glm/glm.hpp>

#include "geometry/aabb.h"
#include "geometry/transform.h"

#include "utils/vec3hash.h"

#include "voxelgridcmp.h"
#include "voxelrenderdata.h"


class Voxel;
class VoxelRenderData;

class VoxelCluster {
public:
    VoxelCluster(float scale);
    virtual ~VoxelCluster();

    Transform& transform();
    void setTransform(const Transform& transform);


    const IAABB& minimalGridAABB();

    const Sphere& minimalGridSphere();

    const IAABB& aabb();
    IAABB aabb(const Transform& transform);

    Voxel* voxel(const glm::ivec3& position);

    virtual void addVoxel(Voxel* voxel);
    virtual void removeVoxel(Voxel* voxel);

    const std::unordered_map<glm::ivec3, Voxel*>& voxelMap() const;
    int voxelCount() const;

    VoxelRenderData* voxelRenderData();

    virtual float emissiveness();


protected:
    std::unordered_map<glm::ivec3, Voxel*> m_voxels;
    VoxelRenderData m_voxelRenderData;
    Transform m_transform;


    std::set<Voxel*, VoxelGridCmp<XAxis, YAxis, ZAxis>> m_voxelsXSorted;
    std::set<Voxel*, VoxelGridCmp<YAxis, XAxis, ZAxis>> m_voxelsYSorted;
    std::set<Voxel*, VoxelGridCmp<ZAxis, XAxis, YAxis>> m_voxelsZSorted;


    void extendGridAABB(Voxel* voxel);
    void shrinkGridAABB(Voxel* voxel);

    void calculateMinimalGridAABB();
    void calculateMinimalGridSphere();
    IAABB calculateAABB(const Transform& transform);


private:
    IAABB m_minimalGridAABB;
    bool m_minimalGridAABBValid;

    Sphere m_minimalGridSphere;
    bool m_minimalGridSphereValid;

    IAABB m_aabb;
    Transform m_cachedAABBTransform;
    bool m_aabbValid;
};

