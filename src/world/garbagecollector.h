#pragma once

#include <list>

class PhysicalVoxelCluster;

class GarbageCollector
{
public:
    void check(std::list<PhysicalVoxelCluster*> &modifiedVoxelClusters);
   //void applyOnGarbageHooks();

    std::list<PhysicalVoxelCluster*> &garbageVoxelClusters();


protected:
    std::list<PhysicalVoxelCluster*> m_garbageVoxelClusters;
};

