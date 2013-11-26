#pragma once

#include <set>
#include <list>

#include "voxel/voxelcluster.h"

#include "voxelclusterorphan.h"


class SplitDetector
{
public:
    void searchOrphans(std::set<VoxelCluster*> &modifiedVoxelClusters);
    std::list<VoxelClusterOrphan*> &voxelClusterOrphans();


protected:
    std::list<VoxelClusterOrphan*> m_voxelClusterOrphans;

    std::set<Voxel*> m_potentialOrphans;

    void fillPotentialOrphans(VoxelCluster *voxelCluster);
    void removeNonOrphans(Voxel *voxel);
};

