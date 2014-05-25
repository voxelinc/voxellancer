#include "garbagecollector.h"

#include "universe/sector.h"

#include "worldobject/worldobject.h"


GarbageCollector::GarbageCollector(Sector& sector):
    m_sector(sector)
{
}

void GarbageCollector::check() {
    m_sector.foreachWorldObject( [&](glow::ref_ptr<WorldObject>& object) {
        if (object->voxelMap().empty()) {
            object->unspawn();
        }
    });
}

