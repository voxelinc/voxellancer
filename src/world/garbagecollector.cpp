#include "garbagecollector.h"

void GarbageCollector::check(std::list<VoxelCluster*> &modifiedVoxelClusters) {

}

std::list<VoxelCluster*> &GarbageCollector::garbageVoxelClusters() {
    return m_garbageVoxelClusters;
}

