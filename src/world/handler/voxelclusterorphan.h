#pragma once

#include <list>

class PhysicalVoxelCluster;
class Voxel;

class VoxelClusterOrphan
{
public:


protected:
    PhysicalVoxelCluster &m_voxelCluster;
    std::list<Voxel*> m_orphanedVoxels;
};

