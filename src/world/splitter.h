#pragma once

#include "voxelclusterorphan.h"


class Splitter
{
public:
    void split(std::list<VoxelClusterOrphan*> &voxelClusterOrphans);
    std::list<VoxelCluster*> &splitOffVoxelClusters();


protected:
    std::list<VoxelCluster*> m_splitOffVoxelClusters;

    VoxelCluster *createVoxelClusterFromOrphan(VoxelClusterOrphan *orphanCluster);
    void removeExtractedVoxelsFromEx(VoxelClusterOrphan *orphanCluster);
};

