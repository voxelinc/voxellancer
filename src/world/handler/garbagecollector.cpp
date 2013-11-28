#include "garbagecollector.h"

void GarbageCollector::check(std::set<WorldObject*> &modifiedVoxelClusters) {

}

std::set<WorldObject*> &GarbageCollector::garbageVoxelClusters() {
    return m_garbageVoxelClusters;
}

