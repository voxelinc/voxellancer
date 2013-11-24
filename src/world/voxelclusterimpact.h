#pragma once

#include <list>

#include "voxel/voxelcluster.h"

#include "voxelimpact.h"


class VoxelClusterImpact
{
public:
    VoxelClusterImpact(VoxelCluster &voxelCluster);


protected:
    VoxelCluster &m_voxelCluster;
    std::list<VoxelImpact*> voxelImpacts;
};

