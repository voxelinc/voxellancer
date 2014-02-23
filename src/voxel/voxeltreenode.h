#pragma once

#include <set>
#include <vector>

#include <glm/glm.hpp>

#include "geometry/sphere.h"
#include "geometry/gridaabb.h"


class Voxel;
class VoxelTree;

class VoxelTreeNode
{
public:
    VoxelTreeNode(int octIndex, VoxelTree* voxelTree, VoxelTreeNode *parent, const GridAABB& gridAABB);
    VoxelTreeNode(VoxelTree* voxelTree, const GridAABB& gridAABB, VoxelTreeNode* initialSubnode);
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

    const GridAABB& gridAABB() const;

    Sphere& sphere();
    Sphere& sphere(const Transform& transform);

    bool active() const;
    void setActive(bool active);

    void insert(Voxel* voxel);
    void remove(Voxel* voxel);


protected:
    int m_octIndex;

    VoxelTreeNode* m_parent;
    VoxelTree* m_voxelTree;

    GridAABB m_gridAABB;

    Sphere m_sphere;
    Transform m_cachedSphereTransform;

    bool m_active;

    std::vector<VoxelTreeNode*> m_subnodes;
    std::list<VoxelTreeNode*> m_activeSubnodes;

    Voxel* m_voxel;


    void toGroup();

    void subnodeActivated(VoxelTreeNode* subnode);
    void subnodeDeactivated(VoxelTreeNode* subnode);

    VoxelTreeNode* cellSubnode(const glm::ivec3& cell);

    void calculateSpherePosition(const Transform& transform);
    void calculateSphereRadius(const Transform& transform);
};

