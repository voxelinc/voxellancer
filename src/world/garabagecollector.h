#pragma once

#include <list>

#include "voxel/voxelcluster.h"


class GarbageCollector
{
public:
    void check(std::list<VoxelCluster*> &modifiedVoxelClusters);
    void applyOnGarbageHooks();

    std::list<VoxelCluster*> &garbageVoxelClusters();
};

