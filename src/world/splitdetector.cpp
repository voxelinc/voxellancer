#include "splitdetector.h"

void SplitDetector::searchOrphans(std::set<VoxelCluster*> &modifiedVoxelClusters) {

}

std::list<VoxelClusterOrphan*> &SplitDetector::voxelClusterOrphans() {
    return m_voxelClusterOrphans;
}
