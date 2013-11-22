#include "wrecker.h"

void Wrecker::detectWreckages(std::list<VoxelCluster*> &modifiedVoxelClusters) {
    m_wreckages.clear();
}

std::list<VoxelCluster*> &Wrecker::wreckages() {
    return m_wreckages;
}


std::list<VoxelCluster*> &Wrecker::recycled() {
    return m_recycled;
}
