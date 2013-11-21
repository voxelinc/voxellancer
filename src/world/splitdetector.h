#pragma once


class SplitDetector
{
public:
    void searchOrphans(std::list<VoxelCluster*> &modifiedVoxelClusters);
    std::list<VoxelClusterOrphan*> &voxelClusterOrphans();
};
