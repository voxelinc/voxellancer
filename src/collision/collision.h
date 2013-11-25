#pragma once


class WorldTreeVoxelCluster;
class Voxel;

class Collision
{
public:
    Collision(Voxel *voxelA, Voxel *voxelB, WorldTreeVoxelCluster * voxelClusterA, WorldTreeVoxelCluster * voxelClusterB);
    virtual ~Collision();

    const WorldTreeVoxelCluster * voxelClusterA() const;
    WorldTreeVoxelCluster * voxelClusterA();
    
    const WorldTreeVoxelCluster * voxelClusterB() const;
    WorldTreeVoxelCluster * voxelClusterB();

    Voxel *voxelA();
    const Voxel *voxelA() const;

    Voxel *voxelB();
    const Voxel *voxelB() const;

protected:
    Voxel *m_voxelA;
    Voxel *m_voxelB;
    WorldTreeVoxelCluster *m_voxelClusterA;
    WorldTreeVoxelCluster *m_voxelClusterB;
};

