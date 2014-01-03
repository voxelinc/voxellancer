#pragma once


class Voxel;
class WorldObject;
class VoxelTreeNode;

class VoxelTree {
public:
    VoxelTree(WorldObject* worldObject);
    ~VoxelTree();

    VoxelTreeNode* root();

    void insert(Voxel* voxel);
    void remove(Voxel* voxel);

    WorldObject* worldObject();


protected:
    VoxelTreeNode* m_root;
    WorldObject* m_worldObject;

    void extend();
};
