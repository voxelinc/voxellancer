#include "voxeltree.h"

#include "utils/tostring.h"

#include "worldobject/worldobject.h"

#include "voxel.h"
#include "voxeltreenode.h"


VoxelTree::VoxelTree(WorldObject* worldObject):
    m_root(new VoxelTreeNode(0, this, nullptr, Grid3dAABB(glm::ivec3(0, 0, 0), glm::ivec3(0, 0, 0)))),
    m_worldObject(worldObject)
{

}

VoxelTree::~VoxelTree() {
    delete m_root;
}

VoxelTreeNode* VoxelTree::root() {
    assert(m_root->parent() == nullptr);
    return m_root;
}

void VoxelTree::insert(Voxel* voxel) {
    while(!m_root->gridAABB().contains(voxel->gridCell())) {
        extend();
    }
    m_root->insert(voxel);
}

void VoxelTree::remove(Voxel* voxel) {
    voxel->voxelTreeNode()->remove(voxel);
}

WorldObject* VoxelTree::worldObject() {
    return m_worldObject;
}

void VoxelTree::extend() {
    m_root = new VoxelTreeNode(this, Grid3dAABB(glm::ivec3(0, 0, 0), m_root->gridAABB().rub()*2 + glm::ivec3(1, 1, 1)), m_root);
}

