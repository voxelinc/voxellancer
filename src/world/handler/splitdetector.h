#pragma once

#include <set>
#include <list>

class WorldObjectSplit;
class WorldObject;
class Voxel;

class SplitDetector
{
public:
    void searchSplitOffs(std::set<WorldObject*> &modifiedWorldObject);
    std::list<WorldObjectSplit*> &worldObjectSplits();


protected:
    std::list<WorldObjectSplit*> m_worldObjectSplits;
    WorldObject *m_currentWorldObject;

    std::set<Voxel*> m_potentialOrphans;

    void clear();
    void fillPotentialOrphans();
    WorldObjectSplit *unmarkContinuousVoxels(Voxel *orphanVoxel);
};

