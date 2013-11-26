#pragma once

#include <list>

class VoxelClusterOrphan;
class PhysicalVoxelCluster;

class SplitDetector
{
public:
    void searchOrphans(std::list<PhysicalVoxelCluster*> &modifiedVoxelClusters);
    std::list<VoxelClusterOrphan*> &voxelClusterOrphans();


protected:
    std::list<VoxelClusterOrphan*> m_voxelClusterOrphans;
};

