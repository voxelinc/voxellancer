#include "collision.h"

#include "physics/physicalvoxel.h"
#include "physics/physicalvoxelcluster.h"


Collision::Collision(PhysicalVoxel *physicalVoxelA, PhysicalVoxel *physicalVoxelB, PhysicalVoxelCluster* physicalVoxelClusterA, PhysicalVoxelCluster* physicalVoxelClusterB) :
    m_physicalVoxelA(physicalVoxelA),
    m_physicalVoxelB(physicalVoxelB),
    m_physicalVoxelClusterA(physicalVoxelClusterA),
    m_physicalVoxelClusterB(physicalVoxelClusterB)
{

}

PhysicalVoxel* Collision::physicalVoxelA() {
    return m_physicalVoxelA;
}

const PhysicalVoxel* Collision::physicalVoxelA() const {
    return m_physicalVoxelA;
}

PhysicalVoxel* Collision::physicalVoxelB() {
    return m_physicalVoxelB;
}

const PhysicalVoxel* Collision::physicalVoxelB() const {
    return m_physicalVoxelB;
}

PhysicalVoxelCluster* Collision::physicalVoxelClusterA() {
    return m_physicalVoxelClusterA;
}

PhysicalVoxelCluster* Collision::physicalVoxelClusterB() {
    return m_physicalVoxelClusterB;
}
