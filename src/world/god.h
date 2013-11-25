#pragma once

#include <list>

#include "voxel/voxelcluster.h"


class World;

class God
{
public:
    God();
    virtual ~God();

    std::list<VoxelCluster*> &voxelClusters();

    void scheduleSpawns(const std::list<VoxelCluster*> &spawns);
    void scheduleRemovals(const std::list<VoxelCluster*> &removals);

    void spawn();
    void remove();


protected:
    std::list<VoxelCluster*> m_voxelClusters;
    std::list<VoxelCluster*> m_scheduledSpawns;
    std::list<VoxelCluster*> m_scheduledRemovals;
};
