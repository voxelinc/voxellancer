#include "collision.h"


Collision::Collision(Voxel *voxelA, Voxel *voxelB, WorldTreeVoxelCluster * voxelClusterA, WorldTreeVoxelCluster * voxelClusterB) :
    m_voxelA(voxelA),
    m_voxelB(voxelB),
    m_voxelClusterA(voxelClusterA),
    m_voxelClusterB(voxelClusterB)
{

}

Collision::~Collision() {

}

Voxel *Collision::voxelA() {
    return m_voxelA;
}

const Voxel *Collision::voxelA() const {
    return m_voxelA;
}

Voxel *Collision::voxelB() {
    return m_voxelB;
}

const Voxel *Collision::voxelB() const {
    return m_voxelB;
}

WorldTreeVoxelCluster * Collision::voxelClusterA() {
    return m_voxelClusterA;
}

WorldTreeVoxelCluster * Collision::voxelClusterB() {
    return m_voxelClusterB;
}
