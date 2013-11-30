#pragma once


class CollidableVoxelCluster;
class Voxel;

class Collision
{
public:
    Collision(Voxel *voxelA, Voxel *voxelB, CollidableVoxelCluster * voxelClusterA, CollidableVoxelCluster * voxelClusterB);
    virtual ~Collision();

    CollidableVoxelCluster * voxelClusterA();
    
    CollidableVoxelCluster * voxelClusterB();

    Voxel *voxelA();
    const Voxel *voxelA() const;

    Voxel *voxelB();
    const Voxel *voxelB() const;

protected:
    Voxel *m_voxelA;
    Voxel *m_voxelB;
    CollidableVoxelCluster *m_voxelClusterA;
    CollidableVoxelCluster *m_voxelClusterB;
};

