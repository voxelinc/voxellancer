#pragma once

#include <glm/glm.hpp>

#include <geometry/commontransform.h>
#include <geometry/sphere.h>

class VoxeltreeNode
{
public:
    VoxeltreeNode(Voxelcluster &voxelcluster, const IAABB &gridAABB);
    virtual ~VoxeltreeNode();

    bool isAtomic();

    std::list<VoxeltreeNode*> &subnodes();
    const std::list<VoxeltreeNode*> &subnodes() const;

    Voxel *voxel();
    const Voxel *voxel() const;

    void insert(Voxel *voxel);
    void remove(const glm::ivec3 &cell);




protected:
    Voxelcluster &m_voxelcluster;
    Sphere m_absoluteBoundingSphere;
    IAABB m_gridAABB;

    CommonTransform m_transformCache;
    std::vector<VoxeltreeNode*> m_subnodes;
    Voxel *m_voxel;

    void split();
    void unsplit();
    void octuple();
};

