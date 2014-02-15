#pragma once

#include <unordered_set>

class WorldObject;

class GarbageCollector
{
public:
    void check(std::unordered_set<WorldObject*> &modifiedVoxelClusters);
   //void applyOnGarbageHooks();

    std::list<WorldObject*> &garbageVoxelClusters();


protected:
    std::list<WorldObject*> m_garbageVoxelClusters;
};

