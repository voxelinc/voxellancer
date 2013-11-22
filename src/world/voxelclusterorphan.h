#pragma once

#include <list>

#include "voxel/voxelcluster.h"


class VoxelClusterOrphan
{
public:


protected:
    VoxelCluster &m_voxelCluster;
    std::list<Voxel*> m_orphanedVoxels;
};

