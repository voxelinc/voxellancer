#include "splitdetector.h"

#include "world/helper/worldobjectsplit.h"

#include "voxel/voxel.h"
#include "voxel/voxelneighbourhelper.h"

#include "worldobject/worldobject.h"


void SplitDetector::searchSplitOffs(std::set<WorldObject*> &modifiedWorldObjects) {
    clear();

    for(WorldObject *modifiedWorldObject : modifiedWorldObjects) {
        m_currentWorldObject = modifiedWorldObject;

        fillPotentialOrphans();

        if(m_currentWorldObject->crucialVoxel() != nullptr) {
            unmarkContinuousVoxels(m_currentWorldObject->crucialVoxel());
        }
        else {
            unmarkContinuousVoxels(m_currentWorldObject->voxelMap().begin()->second);
        }

        while(!m_potentialOrphans.empty()) {
            WorldObjectSplit *split = unmarkContinuousVoxels(*m_potentialOrphans.begin());
            split->setExWorldObject(m_currentWorldObject);
            m_worldObjectSplits.push_back(split);
        }
    }
}

std::list<WorldObjectSplit*> &SplitDetector::worldObjectSplits() {
    return m_worldObjectSplits;
}

void SplitDetector::clear() {
    for(WorldObjectSplit *split : m_worldObjectSplits) {
        delete split;
    }

    m_worldObjectSplits.clear();
    m_potentialOrphans.clear();
}

/**
* Marks all voxels in the cluster as potential orphans, they are later unmarked by unmarkContinuousVoxels()
**/
void SplitDetector::fillPotentialOrphans() {
    m_potentialOrphans.clear();

    for(const std::pair<glm::ivec3, Voxel*> &cellVoxelPair : m_currentWorldObject->voxelMap()) {
        m_potentialOrphans.insert(cellVoxelPair.second);
    }
}

/**
* Starting from voxel, this function recursivly builds up a set of voxels that are attached to each other with facing sides
**/
WorldObjectSplit *SplitDetector::unmarkContinuousVoxels(Voxel *voxel) {
    WorldObjectSplit *continuousCluster;

    continuousCluster = new WorldObjectSplit;

    std::set<Voxel*>::iterator i = m_potentialOrphans.find(voxel);

    if(i == m_potentialOrphans.end()) { // We've been here already, so nothing to do here
        return continuousCluster;
    }

    continuousCluster->addVoxel(*i);
    m_potentialOrphans.erase(i);

    std::list<Voxel*> neighbours = VoxelNeighbourHelper(m_currentWorldObject, voxel, false).neighbours();

    for(Voxel *neighbour : neighbours) {
        WorldObjectSplit *neighbourOrphan = unmarkContinuousVoxels(neighbour);
        continuousCluster->addAllVoxels(neighbourOrphan);
        delete neighbourOrphan;
    }

    return continuousCluster;
}

