#pragma once

#include <list>
#include <unordered_set>


class WorldObject;

class GarbageCollector {
public:
    void check(std::unordered_set<WorldObject*> &modifiedVoxelClusters);
};

