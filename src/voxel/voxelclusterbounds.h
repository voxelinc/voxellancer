#pragma once

#include <set>

#include "geometry/aabb.h"
#include "geometry/gridaabb.h"
#include "geometry/sphere.h"

#include "voxelgridcmp.h"


class Voxel;
class VoxelCluster;

/*
    This class stores and calculates bound-informations of
    a voxelcluster. It is optimized for speed which means:

    * It uses sorted sets on each axis to be able to recalc the GridAABBB fast on voxel addition or removal
    * The aabb is only recalculated if the cluster or the passed transform changes, since it is very likely that
        the same transform will be queried multiple times during e.g. Worldtreequeries and collisiondetection
    * The aabb is stored in an I(nteger)AABB because it is only an estimation anyway and calculation on integers
        are faster than on float AND this function is queried quite frequently
*/
class VoxelClusterBounds {
public:
    VoxelClusterBounds(VoxelCluster* voxelCluster);

    void addVoxel(Voxel* voxel);
    void removeVoxel(Voxel* voxel);

    const GridAABB& minimalGridAABB();
    const Sphere& minimalGridSphere();

    /*
        The aabb is stored in an I(nteger)AABB because it is only an estimation anyway and calculation on integers
        are faster than on float AND this function is queried quite frequently
    */
    const IAABB& aabb();
    IAABB aabb(const Transform& transform);

    const Sphere& sphere();
    Sphere sphere(const Transform& transform);



protected:
    VoxelCluster* m_voxelCluster;

    std::set<Voxel*, VoxelGridCmp<XAxis, YAxis, ZAxis>> m_voxelsXSorted;
    std::set<Voxel*, VoxelGridCmp<YAxis, XAxis, ZAxis>> m_voxelsYSorted;
    std::set<Voxel*, VoxelGridCmp<ZAxis, XAxis, YAxis>> m_voxelsZSorted;

    void calculateMinimalGridAABB();
    void calculateMinimalGridSphere();
    const IAABB calculateAABB(const Transform& transform);


private:
    GridAABB m_minimalGridAABB;
    bool m_minimalGridAABBValid;

    Sphere m_minimalGridSphere;
    bool m_minimalGridSphereValid;

    IAABB m_aabb;
    Transform m_cachedAABBTransform;
    bool m_aabbValid;

    Sphere m_sphere;
};

