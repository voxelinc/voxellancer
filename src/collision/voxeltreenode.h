#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "geometry/sphere.h"
#include "geometry/grid3daabb.h"

#include "voxel/voxel.h"

#include "worldtransform.h"


class WorldObject;

class VoxelTreeNode
{
public:
    VoxelTreeNode(WorldObject *worldobject = nullptr, VoxelTreeNode *parent = nullptr, const Grid3dAABB &gridAABB = Grid3dAABB(glm::ivec3(0, 0, 0), glm::ivec3(0, 0, 0)));
    virtual ~VoxelTreeNode();

    bool isAtomic() const;
    bool isVoxel() const;
    bool isLeaf() const;
    bool isEmpty() const;

    std::vector<VoxelTreeNode*> &subnodes();
    const std::vector<VoxelTreeNode*> &subnodes() const;

    Voxel *voxel();
    const Voxel *voxel() const;

    WorldObject* worldObject();

    const Grid3dAABB &gridAABB() const;

    Sphere& boundingSphere();

    void insert(Voxel *physicalVoxel);
    void remove(const glm::ivec3 &cell);


protected:
    VoxelTreeNode *m_parent;
    WorldObject *m_worldObject;

    Grid3dAABB m_gridAABB;

    std::vector<VoxelTreeNode*> m_subnodes;
    Voxel *m_voxel;

    Sphere m_boundingSphere;
    bool m_boundingSphereRadiusValid;
    WorldTransform m_boundingSphereTransform;

    void split();
    void unsplit();
    void octuple();
    void calculateBoundingSpherePosition();
    void calculateBoundingSphereRadius();
};

