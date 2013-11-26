#pragma once

#include <list>

class PhysicalVoxelCluster;


class Wrecker
{
public:
    void detectWreckages(std::list<PhysicalVoxelCluster*> &modifiedVoxelClusters);
    //void applyOnWreckageHooks();
    std::list<PhysicalVoxelCluster*> &wreckages();
    std::list<PhysicalVoxelCluster*> &recycled();

protected:
    std::list<PhysicalVoxelCluster*> m_wreckages;
    std::list<PhysicalVoxelCluster*> m_recycled;
};

