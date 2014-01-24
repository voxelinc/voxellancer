#pragma once

#include <set>

#include "geometry/aabb.h"
#include "geometry/sphere.h"

#include "voxelgridcmp.h"


class Voxel;
class VoxelCluster;

class VoxelClusterBounds {
public:
    VoxelClusterBounds(VoxelCluster* voxelCluster);

    void addVoxel(Voxel* voxel);
    void removeVoxel(Voxel* voxel);

    const IAABB& minimalGridAABB();
    const Sphere& minimalGridSphere();

    const IAABB& aabb();
    IAABB aabb(const WorldTransform& transform);

    const Sphere& sphere();
    Sphere sphere(const WorldTransform& transform);


protected:
    VoxelCluster* m_voxelCluster;

    std::set<Voxel*, VoxelGridCmp<XAxis, YAxis, ZAxis>> m_voxelsXSorted;
    std::set<Voxel*, VoxelGridCmp<YAxis, XAxis, ZAxis>> m_voxelsYSorted;
    std::set<Voxel*, VoxelGridCmp<ZAxis, XAxis, YAxis>> m_voxelsZSorted;

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

    Sphere m_sphere;
};

