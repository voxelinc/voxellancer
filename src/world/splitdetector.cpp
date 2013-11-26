#include "splitdetector.h"

#include "voxel/voxelneighbourhelper.h"


void SplitDetector::searchOrphans(std::set<VoxelCluster*> &modifiedVoxelClusters) {
    m_voxelClusterOrphans.clear();

    for(VoxelCluster *modifiedVoxelCluster : modifiedVoxelClusters) {
        fillPotentialOrphans(modifiedVoxelCluster);
        removeNonOrphans(modifiedVoxelCluster->crucialVoxel());

        while(!m_potentialOrphans.empty()) {
            buildOrphan(nullptr, *m_potentialOrphans.begin());
        }
    }
}

std::list<VoxelClusterOrphan*> &SplitDetector::voxelClusterOrphans() {
    return m_voxelClusterOrphans;
}

void SplitDetector::fillPotentialOrphans(VoxelCluster *voxelCluster) {
    m_potentialOrphans.clear();

    for(std::pair<cvec3, Voxel> &cellVoxelPair : voxelCluster->voxelMap()) {
        m_potentialOrphans.insert(&cellVoxelPair.second);
    }
}

void SplitDetector::removeNonOrphans(Voxel *voxel) {
    std::set<Voxel*>::iterator i = m_potentialOrphans.find(voxel);

    if(i == m_potentialOrphans.end()) { // We've been here already, so nothing to do here
        return;
    }

    m_potentialOrphans.erase(i);

    std::list<Voxel*> neightbours = VoxelNeighbourHelper(voxel, false);

    for(Voxel *neighbour : neighbours) {
        removeNonOrphans(neighbour);
    }
}

void SplitDetector::createOrphan(VoxelClusterOrphan *orphanCluster, Voxel *orphanVoxel) {


}

