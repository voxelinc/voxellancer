#pragma once


class PhysicalVoxelCluster;
class PhysicalVoxel;

class Collision
{
public:
    Collision(PhysicalVoxel* physicalVoxelA, PhysicalVoxel* physicalVoxelB, PhysicalVoxelCluster* physicalVoxelClusterA, PhysicalVoxelCluster* physicalVoxelClusterB);

    PhysicalVoxelCluster* physicalVoxelClusterA();
    PhysicalVoxelCluster* physicalVoxelClusterB();

    PhysicalVoxel* physicalVoxelA();
    const PhysicalVoxel* physicalVoxelA() const;

    PhysicalVoxel* physicalVoxelB();
    const PhysicalVoxel* physicalVoxelB() const;


protected:
    PhysicalVoxel *m_physicalVoxelA;
    PhysicalVoxel *m_physicalVoxelB;
    PhysicalVoxelCluster *m_physicalVoxelClusterA;
    PhysicalVoxelCluster *m_physicalVoxelClusterB;
};

