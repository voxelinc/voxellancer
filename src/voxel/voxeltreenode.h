#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "geometry/sphere.h"
#include "geometry/grid3daabb.h"

#include "voxel/voxel.h"

#include "worldtransform.h"


class PhysicalVoxel;
class PhysicalVoxelCluster;

class VoxelTreeNode
{
public:
    VoxelTreeNode(VoxelTreeNode *parent, PhysicalVoxelCluster *physicalVoxelCluster, const Grid3dAABB &gridAABB = Grid3dAABB(glm::ivec3(0, 0, 0), glm::ivec3(0, 0, 0)));
    VoxelTreeNode(const VoxelTreeNode& other, PhysicalVoxelCluster *physicalVoxelCluster);
	VoxelTreeNode(const VoxelTreeNode& other) = delete; //no "normal" copy ctor
    virtual ~VoxelTreeNode();

    bool isAtomic() const;
    bool isLeaf() const;

    std::vector<VoxelTreeNode*> &subnodes();
    const std::vector<VoxelTreeNode*> &subnodes() const;

    PhysicalVoxel *physicalVoxel();
    const PhysicalVoxel *physicalVoxel() const;

    const Grid3dAABB &gridAABB() const;

    Sphere boundingSphere();

    void insert(PhysicalVoxel *physicalVoxel);
    void remove(const cvec3 &cell);


protected:
    VoxelTreeNode *m_parent;
    PhysicalVoxelCluster *m_physicalVoxelCluster;
    Grid3dAABB m_gridAABB;

    std::vector<VoxelTreeNode*> m_subnodes;
    Voxel *m_voxel;

    void split();
    void unsplit();
    void octuple();
};

