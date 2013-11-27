#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "geometry/sphere.h"
#include "geometry/grid3daabb.h"

#include "voxel/voxel.h"

#include "worldtransform.h"


class CollidableVoxelCluster;

class VoxelTreeNode
{
public:
    VoxelTreeNode(VoxelTreeNode *parent, CollidableVoxelCluster &voxelcluster, const Grid3dAABB &gridAABB = Grid3dAABB(glm::ivec3(0, 0, 0), glm::ivec3(0, 0, 0)));
    VoxelTreeNode(const VoxelTreeNode& other, CollidableVoxelCluster *voxelcluster);
	VoxelTreeNode(const VoxelTreeNode& other) = delete; //no "normal" copy ctor
    virtual ~VoxelTreeNode();

    bool isAtomic() const;
    bool isLeaf() const;

    std::vector<VoxelTreeNode*> &subnodes();
    const std::vector<VoxelTreeNode*> &subnodes() const;

    Voxel *voxel();
    const Voxel *voxel() const;

    const Grid3dAABB &gridAABB() const;

    Sphere boundingSphere();

    void insert(Voxel *voxel);
    void remove(const cvec3 &cell);


protected:
    VoxelTreeNode *m_parent;
    CollidableVoxelCluster &m_voxelcluster;
    Grid3dAABB m_gridAABB;

    std::vector<VoxelTreeNode*> m_subnodes;
    Voxel *m_voxel;

    void split();
    void unsplit();
    void octuple();
};

