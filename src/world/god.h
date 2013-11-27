#pragma once

#include <list>

class PhysicalVoxelCluster;
class World;

class God
{
public:
    God(World & world);
    virtual ~God();

    void scheduleSpawn(PhysicalVoxelCluster *cluster);
    void scheduleSpawns(const std::list<PhysicalVoxelCluster*> &spawns);
    void scheduleRemoval(PhysicalVoxelCluster *cluster);
    void scheduleRemovals(const std::list<PhysicalVoxelCluster*> &removals);

    void spawn();
    void remove();
protected:
    World & m_world;
    std::list<PhysicalVoxelCluster*> m_scheduledSpawns;
    std::list<PhysicalVoxelCluster*> m_scheduledRemovals;
};
