#include "garbagecollector.h"

#include "worldobject/worldobject.h"


void GarbageCollector::check(std::list<glow::ref_ptr<WorldObject>>& objects) {
    for (glow::ref_ptr<WorldObject>& object : objects) {
        if (object->voxelMap().empty()) {
            object->scheduleRemoval();
        }
    }
}

