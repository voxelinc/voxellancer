#include "splitter.h"

#include "world/helper/worldobjectsplit.h"

#include "worldobject/worldobject.h"
#include "voxel/voxel.h"

void Splitter::split(std::list<WorldObjectSplit*> &splits) {
    m_splitOffWorldObjects.clear();

    for(WorldObjectSplit *split : splits) {
        WorldObject *worldObject = createWorldObjectFromOrphan(split);
        m_splitOffWorldObjects.push_back(worldObject);
        removeExtractedVoxelsFromEx(split);
    }
}

std::list<WorldObject*> &Splitter::splitOffWorldObjects() {
    return m_splitOffWorldObjects;
}

WorldObject *Splitter::createWorldObjectFromOrphan(WorldObjectSplit *split) {
    WorldObject *worldObject;

    worldObject = new WorldObject(split->exWorldObject()->transform());
    worldObject->hudInfo().setName(split->exWorldObject()->hudInfo().name() + " - splitoff");
    worldObject->physics().setSpeed(worldObject->physics().speed());
    worldObject->physics().setAngularSpeed(worldObject->physics().angularSpeed());

    for(Voxel *voxel : split->splitOffVoxels()) {
        Voxel *voxelClone = new Voxel(*voxel);
        worldObject->addVoxel(voxelClone);
    }

    worldObject->recalculateCenterAndMass();

    return worldObject;
}

void Splitter::removeExtractedVoxelsFromEx(WorldObjectSplit *split) {
    for(Voxel *voxel : split->splitOffVoxels()) {
        split->exWorldObject()->removeVoxel(voxel->gridCell());
    }
}

