#pragma once

#include <set>
#include <list>

#include "voxel/voxelcluster.h"


class GarbageCollector
{
public:
    void check(std::set<VoxelCluster*> &modifiedVoxelClusters);
   //void applyOnGarbageHooks();

    std::list<VoxelCluster*> &garbageVoxelClusters();


protected:
    std::list<VoxelCluster*> m_garbageVoxelClusters;
};

