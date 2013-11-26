#include "splitdetector.h"

void SplitDetector::searchOrphans(std::list<PhysicalVoxelCluster*> &modifiedVoxelClusters) {

}

std::list<VoxelClusterOrphan*> &SplitDetector::voxelClusterOrphans() {
    return m_voxelClusterOrphans;
}
