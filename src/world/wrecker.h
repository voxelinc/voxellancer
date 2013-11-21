#pragma once


class Wrecker
{
public:
    void detectWreckages(std::list<VoxelCluster*> &modifiedVoxelClusters);
    void applyOnWreckageHooks();
    std::list<VoxelCluster*> &wreckages();
};
