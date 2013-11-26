#include "garbagecollector.h"

void GarbageCollector::check(std::list<PhysicalVoxelCluster*> &modifiedVoxelClusters) {

}

std::list<PhysicalVoxelCluster*> &GarbageCollector::garbageVoxelClusters() {
    return m_garbageVoxelClusters;
}

