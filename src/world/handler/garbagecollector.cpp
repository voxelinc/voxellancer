#include "garbagecollector.h"

void GarbageCollector::check(std::set<WorldObject*> &modifiedVoxelClusters) {

}

std::list<WorldObject*> &GarbageCollector::garbageVoxelClusters() {
    return m_garbageVoxelClusters;
}

