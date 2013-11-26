#include "wrecker.h"

void Wrecker::detectWreckages(std::list<PhysicalVoxelCluster*> &modifiedVoxelClusters) {
    m_wreckages.clear();
}

std::list<PhysicalVoxelCluster*> &Wrecker::wreckages() {
    return m_wreckages;
}


std::list<PhysicalVoxelCluster*> &Wrecker::recycled() {
    return m_recycled;
}
