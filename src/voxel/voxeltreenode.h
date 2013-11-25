#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "geometry/sphere.h"
#include "geometry/grid3daabb.h"

#include "voxel/voxel.h"

#include "worldtransform.h"


class WorldTreeVoxelCluster;

class VoxeltreeNode
{
public:
    VoxeltreeNode(VoxeltreeNode *parent, WorldTreeVoxelCluster &voxelcluster, const Grid3dAABB &gridAABB = Grid3dAABB(glm::ivec3(0, 0, 0), glm::ivec3(0, 0, 0)));
    VoxeltreeNode(const VoxeltreeNode& other, WorldTreeVoxelCluster *voxelcluster);
	VoxeltreeNode(const VoxeltreeNode& other) = delete; //no "normal" copy ctor
    virtual ~VoxeltreeNode();

    bool isAtomic() const;
    bool isLeaf() const;

    std::vector<VoxeltreeNode*> &subnodes();
    const std::vector<VoxeltreeNode*> &subnodes() const;

    Voxel *voxel();
    const Voxel *voxel() const;

    const Grid3dAABB &gridAABB() const;

    Sphere boundingSphere();

    void insert(Voxel *voxel);
    void remove(const cvec3 &cell);


protected:
    VoxeltreeNode *m_parent;
    WorldTreeVoxelCluster &m_voxelcluster;
    Grid3dAABB m_gridAABB;

    std::vector<VoxeltreeNode*> m_subnodes;
    Voxel *m_voxel;

    void split();
    void unsplit();
    void octuple();
};

