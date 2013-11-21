#pragma once


class VoxelClusterOrphan
{
public:


protected:
    VoxelCluster &m_voxelCluster;
    std::list<Voxel*> m_orphanedVoxels;
};

