#pragma once

#include <list>

#include "voxel/voxelcluster.h"


class World;

class God
{
public:
    God(World &world);
    virtual ~God();

    std::list<VoxelCluster*> &voxelClusters();

    void scheduleSpawns(const std::list<VoxelCluster*> &spawns);
    void scheduleRemoval(const std::list<VoxelCluster*> &removals);

    void spawn();
    void remove();


protected:
    World &m_world;
    std::list<VoxelCluster*> m_voxelClusters;
    std::list<VoxelCluster*> m_scheduledSpawns;
    std::list<VoxelCluster*> m_scheduledRemovals;
};
