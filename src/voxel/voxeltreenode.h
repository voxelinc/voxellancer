#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "geometry/sphere.h"
#include "geometry/aabb.h"

#include "voxel/voxel.h"

#include "worldtransform.h"


class VoxelCluster;

class VoxeltreeNode
{
public:
    VoxeltreeNode(VoxeltreeNode *parent, VoxelCluster &voxelcluster, const IAABB &gridAABB);
    virtual ~VoxeltreeNode();

    bool isAtomic() const;
    bool isLeaf() const;

    std::vector<VoxeltreeNode*> &subnodes();
    const std::vector<VoxeltreeNode*> &subnodes() const;

    Voxel *voxel();
    const Voxel *voxel() const;

    const IAABB &gridAABB() const;

    const Sphere &boundingSphere();

    void insert(Voxel *voxel);
    void remove(const glm::ivec3 &cell);


protected:
    VoxeltreeNode *m_parent;
    VoxelCluster &m_voxelcluster;
    Sphere m_boundingSphere;
    IAABB m_gridAABB;
    glm::vec3 m_centerRelPosition;

    WorldTransform m_transformCache;
    std::vector<VoxeltreeNode*> m_subnodes;
    Voxel *m_voxel;

    void split();
    void unsplit();
    void octuple();
    void transform(const WorldTransform &transform);
    void applyTransformCache();
};

