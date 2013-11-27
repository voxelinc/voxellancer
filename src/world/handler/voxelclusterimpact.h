#pragma once

#include <list>
#include "voxelimpact.h"


class VoxelCluster;

class VoxelClusterImpact
{
public:
    VoxelClusterImpact(VoxelCluster &voxelCluster);


protected:
    VoxelCluster &m_voxelCluster;
    std::list<VoxelImpact*> voxelImpacts;
};

