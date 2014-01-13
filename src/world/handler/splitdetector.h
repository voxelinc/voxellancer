#pragma once

#include <list>
#include <unordered_set>

#include "world/helper/worldobjectmodification.h"


class SplitData;
class WorldObject;
class Voxel;

class SplitDetector
{
public:
    void searchSplitOffs(std::list<WorldObjectModification>& worldObjectModifications);

    std::vector<SplitData*> &splitDataList();


protected:
    std::vector<SplitData*> m_splitDataList;

    void clear();
    void findSplits(WorldObject* currentWorldObject, std::unordered_set<Voxel*>& borderVoxel, bool foundSplit = false);
    void createSplit(WorldObject* currentWorldObject, std::unordered_set<Voxel *>& splitVoxels);

};

