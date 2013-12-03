#pragma once

#include <set>
#include <list>

#include "world/helper/worldobjectmodification.h"


class WorldObjectSplit;
class WorldObject;
class Voxel;

class SplitDetector
{
public:
    void searchSplitOffs(std::list<WorldObjectModification> worldObjectModifications);
    std::list<WorldObjectSplit*> &worldObjectSplits();


protected:
    std::list<WorldObjectSplit*> m_worldObjectSplits;
    WorldObject *m_currentWorldObject;

    std::set<Voxel*> m_potentialOrphans;

    void clear();
    void fillPotentialOrphans();
    WorldObjectSplit *unmarkContinuousVoxels(Voxel *orphanVoxel);
};

