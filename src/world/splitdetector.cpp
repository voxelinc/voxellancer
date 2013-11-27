#include "splitdetector.h"

#include "voxel/voxelneighbourhelper.h"


void SplitDetector::searchOrphans(std::set<VoxelCluster*> &modifiedVoxelClusters) {
    clear();

    for(VoxelCluster *modifiedVoxelCluster : modifiedVoxelClusters) {
        fillPotentialOrphans(modifiedVoxelCluster);

        if(modifiedVoxelCluster->crucialVoxel() != nullptr) {
            pollContinuousVoxels(modifiedVoxelCluster->crucialVoxel());
        }

        while(!m_potentialOrphans.empty()) {
            VoxelClusterOrphan *orphanCluster = pollContinuousVoxels(*m_potentialOrphans.begin());
            orphanCluster->setExVoxelCluster(modifiedVoxelCluster);
            m_voxelClusterOrphans.push_back(orphanCluster);
        }
    }
}

std::list<VoxelClusterOrphan*> &SplitDetector::voxelClusterOrphans() {
    return m_voxelClusterOrphans;
}

void SplitDetector::clear() {
    for(VoxelClusterOrphan *orphanCluster : m_voxelClusterOrphans) {
        delete orphanCluster;
    }

    m_voxelClusterOrphans.clear();
    m_potentialOrphans.clear();
}

/**
* Marks all voxels in the cluster as potential orphans, they are later unmarked by pollContinuousVoxels()
**/
void SplitDetector::fillPotentialOrphans(VoxelCluster *voxelCluster) {
    m_potentialOrphans.clear();

    for(const std::pair<cvec3, Voxel> &cellVoxelPair : voxelCluster->voxelMap()) {
        m_potentialOrphans.insert(const_cast<Voxel*>(&cellVoxelPair.second));
    }
}

/**
* Starting from voxel, this function recursivly builds up a set of voxels that are attached to each other with facing sides
**/
VoxelClusterOrphan *SplitDetector::pollContinuousVoxels(Voxel *voxel) {
    VoxelClusterOrphan *continuousCluster;

    continuousCluster = new VoxelClusterOrphan;

    std::set<Voxel*>::iterator i = m_potentialOrphans.find(voxel);

    if(i == m_potentialOrphans.end()) { // We've been here already, so nothing to do here
        return continuousCluster;
    }

    continuousCluster->addVoxel(*i);
    m_potentialOrphans.erase(i);

    std::list<Voxel*> neighbours = VoxelNeighbourHelper(voxel, false).neighbours();

    for(Voxel *neighbour : neighbours) {
        VoxelClusterOrphan *neighbourOrphan = pollContinuousVoxels(neighbour);
        continuousCluster->addAllVoxels(neighbourOrphan);
        delete neighbourOrphan;
    }

    return continuousCluster;
}

