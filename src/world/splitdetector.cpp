#include "splitdetector.h"

void SplitDetector::searchOrphans(std::list<VoxelCluster*> &modifiedVoxelClusters) {

}

std::list<VoxelClusterOrphan*> &SplitDetector::voxelClusterOrphans() {
    return m_voxelClusterOrphans;
}
