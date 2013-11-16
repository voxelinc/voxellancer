#include "collision.h"


Collision::Collision(Voxel *voxelA, Voxel *voxelB):
    m_voxelA(voxelA),
    m_voxelB(voxelB)
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
