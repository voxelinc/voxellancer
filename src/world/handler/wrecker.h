#pragma once

#include <set>
#include <list>

#include "voxel/voxelcluster.h"


class WorldObject;

class Wrecker
{
public:
    void detectWreckages(std::set<WorldObject*> &modifiedVoxelClusters);
    //void applyOnWreckageHooks();
    std::list<WorldObject*> &wreckages();
    std::list<WorldObject*> &recycled();


protected:
    std::list<WorldObject*> m_wreckages;
    std::list<WorldObject*> m_recycled;
};

