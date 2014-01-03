#pragma once

#include <set>
#include <vector>

#include <glm/glm.hpp>

#include "geometry/sphere.h"
#include "geometry/ray.h"
#include "geometry/grid3daabb.h"

#include "voxel/voxel.h"

#include "worldtransform.h"


class VoxelTree;

class VoxelTreeNode
{
public:
    VoxelTreeNode(int octIndex, VoxelTree* voxelTree, VoxelTreeNode *parent, const Grid3dAABB& gridAABB);
    VoxelTreeNode(VoxelTree* voxelTree, const Grid3dAABB& gridAABB, VoxelTreeNode* initialSubnode);
    ~VoxelTreeNode();

    int octIndex() const;

    bool isAtomic() const;
    bool isVoxel() const;
    bool isLeaf() const;
    bool isEmpty() const;

    std::list<VoxelTreeNode*>& subnodes();
    const std::list<VoxelTreeNode*>& subnodes() const;

    Voxel* voxel();
    const Voxel* voxel() const;

    VoxelTree* voxelTree();

    VoxelTreeNode* parent();
    void setParent(VoxelTreeNode* parent);

    const Grid3dAABB& gridAABB() const;

    Sphere& sphere();

    bool active() const;
    void setActive(bool active);

    void insert(Voxel* voxel);
    void remove(Voxel* voxel);


protected:
    int m_octIndex;

    VoxelTreeNode* m_parent;
    VoxelTree* m_voxelTree;

    Grid3dAABB m_gridAABB;

    Sphere m_sphere;
    WorldTransform m_cachedSphereTransform;
    bool m_sphereRadiusValid;

    bool m_active;

    std::vector<VoxelTreeNode*> m_subnodes;
    std::list<VoxelTreeNode*> m_activeSubnodes;

    Voxel* m_voxel;


    void toGroup();

    void subnodeActivated(VoxelTreeNode* subnode);
    void subnodeDeactivated(VoxelTreeNode* subnode);

    VoxelTreeNode* cellSubnode(const glm::ivec3& cell);

    void calculateSpherePosition();
    void calculateSphereRadius();
};

