#include "splitdetector.h"

#include "voxel/voxelneighbourhelper.h"
#include "world/worldobject.h"


void SplitDetector::searchOrphans(std::set<WorldObject*> &modifiedWorldObjects) {
    clear();

    for(WorldObject *modifiedWorldObject : modifiedWorldObjects) {
        m_currentModifiedWorldObject = modifiedWorldObject;

        fillPotentialOrphans();

        if(m_currentModifiedWorldObject->crucialVoxel() != nullptr) {
            pollContinuousVoxels(m_currentModifiedWorldObject->voxelCluster()->crucialVoxel());
        }
        else {
            pollContinuousVoxels(m_currentModifiedWorldObject->voxelCluster()->voxelMap().begin()->first);
        }

        while(!m_potentialOrphans.empty()) {
            VoxelClusterOrphan *orphanCluster = pollContinuousVoxels(*m_potentialOrphans.begin());
            orphanCluster->setExVoxelCluster(m_currentModifiedWorldObject);
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
void SplitDetector::fillPotentialOrphans() {
    m_potentialOrphans.clear();

    for(const std::pair<glm::ivec3, Voxel*> &cellVoxelPair : m_currentModifiedWorldObject()->voxelCluster->voxelMap()) {
        m_potentialOrphans.insert(cellVoxelPair.second);
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

    std::list<Voxel*> neighbours = VoxelNeighbourHelper(m_currentModifiedWorldObject->voxelCluster(), voxel, false).neighbours();

    for(Voxel *neighbour : neighbours) {
        VoxelClusterOrphan *neighbourOrphan = pollContinuousVoxels(neighbour);
        continuousCluster->addAllVoxels(neighbourOrphan);
        delete neighbourOrphan;
    }

    return continuousCluster;
}

