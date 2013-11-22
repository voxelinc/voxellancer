#pragma once

#include <list>

#include "voxel/voxelcluster.h"


class Wrecker
{
public:
    void detectWreckages(std::list<VoxelCluster*> &modifiedVoxelClusters);
    //void applyOnWreckageHooks();
    std::list<VoxelCluster*> &wreckages();
    std::list<VoxelCluster*> &recycled();

protected:
    std::list<VoxelCluster*> m_wreckages;
    std::list<VoxelCluster*> m_recycled;
};

