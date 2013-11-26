#pragma once

#include <list>

class VoxelClusterOrphan;
class PhysicalVoxelCluster;

class Splitter
{
public:
    void split(std::list<VoxelClusterOrphan*> &voxelClusterOrphans);
    std::list<PhysicalVoxelCluster*> &splitOffVoxelClusters();


protected:
    std::list<PhysicalVoxelCluster*> m_splitOffVoxelClusters;
};

