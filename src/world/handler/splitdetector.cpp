#include "splitdetector.h"

#include <unordered_set>
#include <queue>

#include "world/helper/splitdata.h"

#include "voxel/voxel.h"
#include "voxel/voxelneighbourhelper.h"

#include "worldobject/worldobject.h"
#include "glow/AutoTimer.h"


void SplitDetector::searchSplitOffs(std::list<WorldObjectModification>& worldObjectModifications) {
    clear();

    for(WorldObjectModification& worldObjectModification : worldObjectModifications) {
        //glow::AutoTimer t("splitdetection" + worldObjectModification.worldObject()->objectInfo().name());
        //glow::debug("%;", worldObjectModification.removedVoxels().size());

        WorldObject* currentWorldObject = worldObjectModification.worldObject();
        if (currentWorldObject->voxelMap().size() > 1) {
            VoxelNeighbourHelper nHelper(currentWorldObject, true);
            std::unordered_set<Voxel*> borderVoxels;
            for (glm::ivec3 removedPos : worldObjectModification.removedVoxels()) {
                for (Voxel * voxel : nHelper.neighbours(removedPos)) {
                    borderVoxels.insert(voxel);
                }
            }
            findSplits(currentWorldObject, borderVoxels);
        }
    }
}


std::vector<SplitData*> &SplitDetector::splitDataList() {
    return m_splitDataList;
}

void SplitDetector::clear() {
    for(SplitData *split : m_splitDataList) {
        delete split;
    }

    m_splitDataList.clear();
}

void SplitDetector::findSplits(WorldObject* currentWorldObject, std::unordered_set<Voxel*>& borderVoxel, bool addLastSplit) {
    if (borderVoxel.size() == 0)
        return;

    VoxelNeighbourHelper nHelper(currentWorldObject, true);
    std::unordered_set<Voxel *> visited;
    std::queue<Voxel *> toVisit;

    // add one voxel from the border
    Voxel* start = *borderVoxel.begin();
    borderVoxel.erase(start);
    visited.insert(start);
    toVisit.push(start);

    // breadth first search for other border voxels
    while ((borderVoxel.size() > 0 || addLastSplit) && toVisit.size() > 0) {
        Voxel * current = toVisit.front();
        toVisit.pop();

        for (Voxel * voxel : nHelper.neighbours(current)) {
            if (!visited.count(voxel)) {
                borderVoxel.erase(voxel);
                visited.insert(voxel);
                toVisit.push(voxel);
            }
        }
    }

    if (borderVoxel.size() > 0 || addLastSplit) {
        if (currentWorldObject->crucialVoxel() == nullptr || visited.count(currentWorldObject->crucialVoxel()) == 0) {
            createSplit(currentWorldObject, visited);
        }
    }
    if (borderVoxel.size() > 1 || currentWorldObject->crucialVoxel() != nullptr && borderVoxel.size() > 0) {
        findSplits(currentWorldObject, borderVoxel, currentWorldObject->crucialVoxel() != nullptr);
    }
}

void SplitDetector::createSplit(WorldObject* currentWorldObject, std::unordered_set<Voxel *>& splitVoxels) {
    SplitData * split = new SplitData(currentWorldObject);
    for (Voxel * voxel : splitVoxels) {
        split->addVoxel(voxel);
    }
    m_splitDataList.push_back(split);
}



