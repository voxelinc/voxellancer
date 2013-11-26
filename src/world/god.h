#pragma once

#include <list>

class PhysicalVoxelCluster;
class World;

class God
{
public:
    God(World & world);
    virtual ~God();

    std::list<PhysicalVoxelCluster*> &voxelClusters();

    void scheduleSpawns(const std::list<PhysicalVoxelCluster*> &spawns);
    void scheduleRemovals(const std::list<PhysicalVoxelCluster*> &removals);

    void spawn();
    void remove();

protected:
    World & m_world;
    std::list<PhysicalVoxelCluster*> m_voxelClusters;
    std::list<PhysicalVoxelCluster*> m_scheduledSpawns;
    std::list<PhysicalVoxelCluster*> m_scheduledRemovals;
};
