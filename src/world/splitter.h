#pragma once

#include "voxelclusterorphan.h"


class Splitter
{
public:
    void split(std::list<VoxelClusterOrphan*> &voxelClusterOrphans);
    std::list<VoxelCluster*> &splitOffVoxelClusters();
};

