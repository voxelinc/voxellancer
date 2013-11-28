#pragma once

#include <set>
#include <list>

class WorldObject;

class GarbageCollector
{
public:
    void check(std::set<WorldObject*> &modifiedVoxelClusters);
   //void applyOnGarbageHooks();

    std::list<WorldObject*> &garbageVoxelClusters();


protected:
    std::list<WorldObject*> m_garbageVoxelClusters;
};

