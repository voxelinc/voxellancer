#include "splitdetector.h"

void SplitDetector::searchOrphans(std::list<WorldObject*> &modifiedVoxelClusters) {

}

std::list<VoxelClusterOrphan*> &SplitDetector::voxelClusterOrphans() {
    return m_voxelClusterOrphans;
}
