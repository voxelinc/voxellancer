#include "garbagecollector.h"

void GarbageCollector::check(std::set<VoxelCluster*> &modifiedVoxelClusters) {

}

std::list<VoxelCluster*> &GarbageCollector::garbageVoxelClusters() {
    return m_garbageVoxelClusters;
}

