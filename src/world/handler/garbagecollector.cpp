#include "garbagecollector.h"

#include "worldobject/worldobject.h"

void GarbageCollector::check(std::list<WorldObject*> &modifiedVoxelClusters) {
    m_garbageVoxelClusters.clear();
    for (WorldObject* object : modifiedVoxelClusters){
        if (object->voxelMap().size() == 0)
            m_garbageVoxelClusters.push_back(object);
    }
}

std::list<WorldObject*> &GarbageCollector::garbageVoxelClusters() {
    return m_garbageVoxelClusters;
}

