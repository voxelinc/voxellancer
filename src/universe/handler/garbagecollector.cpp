#include "garbagecollector.h"

#include "worldobject/worldobject.h"


void GarbageCollector::check(std::unordered_set<WorldObject*>& modifiedVoxelClusters) {
    for (WorldObject* object : modifiedVoxelClusters) {
        if (object->voxelMap().empty()) {
            object->scheduleRemoval();
        }
    }
}

